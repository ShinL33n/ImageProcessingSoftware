#include "ThreadPool.h"
#include <stdexcept>

ThreadPool::ThreadPool(int numThreads) : m_active(0), m_stop(false) {
    InitializeCriticalSection(&m_cs);
    // Semaphore counts available tasks; workers block here when idle
    m_semaphore = CreateSemaphore(NULL, 0, LONG_MAX, NULL);
    // Manual-reset event: set when m_active reaches 0
    m_doneEvent = CreateEvent(NULL, TRUE, TRUE, NULL);

    for (int i = 0; i < numThreads; ++i) {
        HANDLE h = CreateThread(NULL, 0, workerThread, this, 0, NULL);
        if (h == NULL) throw std::runtime_error("CreateThread failed");
        m_threads.push_back(h);
    }
}

ThreadPool::~ThreadPool() {
    // Signal workers to stop, then wait for them
    m_stop = true;
    ReleaseSemaphore(m_semaphore, (LONG)m_threads.size(), NULL);
    WaitForMultipleObjects((DWORD)m_threads.size(), m_threads.data(), TRUE, INFINITE);
    for (HANDLE h : m_threads) CloseHandle(h);
    CloseHandle(m_semaphore);
    CloseHandle(m_doneEvent);
    DeleteCriticalSection(&m_cs);
}

void ThreadPool::submit(std::function<void()> task) {
    EnterCriticalSection(&m_cs);
    m_queue.push(std::move(task));
    InterlockedIncrement(&m_active);
    ResetEvent(m_doneEvent); // not done yet
    LeaveCriticalSection(&m_cs);
    ReleaseSemaphore(m_semaphore, 1, NULL); // wake one worker
}

void ThreadPool::waitAll() {
    WaitForSingleObject(m_doneEvent, INFINITE);
}

DWORD WINAPI ThreadPool::workerThread(LPVOID param) {
    static_cast<ThreadPool*>(param)->workerLoop();
    return 0;
}

void ThreadPool::workerLoop() {
    while (true) {
        WaitForSingleObject(m_semaphore, INFINITE); // block until task or stop
        if (m_stop) return;

        std::function<void()> task;
        EnterCriticalSection(&m_cs);
        if (!m_queue.empty()) {
            task = std::move(m_queue.front());
            m_queue.pop();
        }
        LeaveCriticalSection(&m_cs);

        if (task) {
            task(); // execute the processing function
            // When last task finishes, signal waitAll()
            if (InterlockedDecrement(&m_active) == 0)
                SetEvent(m_doneEvent);
        }
    }
}
