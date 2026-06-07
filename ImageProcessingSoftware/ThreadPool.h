#pragma once
#include <windows.h>
#include <vector>
#include <queue>
#include <functional>

/// Thread pool using Windows HANDLE threads and CRITICAL_SECTION for synchronization.
/// Tasks are std::function<void()> objects queued and consumed by worker threads.
class ThreadPool {
public:
    explicit ThreadPool(int numThreads);
    ~ThreadPool();

    /// Adds a task to the queue. Thread-safe.
    void submit(std::function<void()> task);

    /// Blocks until all submitted tasks are finished.
    void waitAll();

private:
    static DWORD WINAPI workerThread(LPVOID param);
    void workerLoop();

    std::vector<HANDLE>               m_threads;
    std::queue<std::function<void()>> m_queue;
    CRITICAL_SECTION                  m_cs;        // protects m_queue and m_active
    HANDLE                            m_semaphore; // signals available tasks
    HANDLE                            m_doneEvent; // signals all tasks complete
    volatile long                     m_active;    // tasks currently running or queued
    volatile bool                     m_stop;
};
