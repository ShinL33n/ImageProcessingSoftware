/**
 * EdgeDetect - Image processing application
 * Reads config from .ini, loads images from source folder,
 * applies Canny edge detection multithreadedly, saves results
 * and thumbnail collages to destination folder.
 *
 * Usage: EdgeDetect.exe config.ini
 */
using namespace std;
#ifdef _DEBUG
    #define _CRTDBG_MAP_ALLOC
    #include <crtdbg.h>
#endif

#include <iostream>
#include <string>
#include <windows.h>
#include <chrono>

#include "ConfigReader.h"
#include "ResultWriter.h"
#include "ImageLoader.h"
#include "ThumbnailBuilder.h"
#include "ImageProcessor.h"
#include "ThreadPool.h"

// Mutex protecting access to shared ThumbnailBuilder instances from worker threads
static CRITICAL_SECTION g_thumbCS;

// Thread-safe success / failure counters for the final summary (UC-01)
static volatile long g_success = 0;
static volatile long g_failed = 0;

int main(int argc, char* argv[])
{
    #ifdef _DEBUG
        // Dump any memory leaks to the debug output at program exit.
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    #endif

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " config.ini\n";
        return 1;
    }

    auto tStart = std::chrono::steady_clock::now();

    // Load configuration
    ConfigReader config;
    if (!config.load(argv[1])) return 1;

    cout << "[Main] Source:      " << config.sourcePath << "\n"
         << "[Main] Destination: " << config.destPath << "\n"
         << "[Main] Threads:     " << config.threadCount << "\n";

    //Scan source folder
    ImageLoader loader(config.sourcePath);
    if (loader.count() == 0) {
        cerr << "[Main] No images found. Exiting \n";
        return 1;
    }

    // Prepare output helpers
    ResultWriter     writer(config.destPath);
    ThumbnailBuilder srcThumbs(cv::Size(config.thumbWidth, config.thumbHeight), config.thumbColumns);
    ThumbnailBuilder dstThumbs(cv::Size(config.thumbWidth, config.thumbHeight), config.thumbColumns);

    InitializeCriticalSection(&g_thumbCS);

    // Submit processing tasks to thread pool
    // Each task: load -> process -> save result -> add to collages (thread-safe)
    {
        ThreadPool pool(config.threadCount);
        ImageProcessor processor; // stateless - safe to share across tasks

        for (size_t i = 0; i < loader.count(); ++i) {
            pool.submit([&, i]() {
                // Per-thread exception handling: a failure on one image must NOT
                // crash the program or abort the remaining images
                try {
                    // Load original image
                    cv::Mat src = loader.loadAt(i);
                    if (src.empty()) {
                        InterlockedIncrement(&g_failed);
                        return;
                    }

                    // Run edge detection
                    cv::Mat edges = processor.process(src);

                    // Derive output filename from original path
                    const std::string& srcPath = loader.filePaths()[i];
                    size_t slash = srcPath.find_last_of("\\/");
                    std::string filename = (slash == std::string::npos) ? srcPath : srcPath.substr(slash + 1);

                    // Save processed image and count the outcome
                    if (writer.saveImage(edges, filename))
                        InterlockedIncrement(&g_success);
                    else
                        InterlockedIncrement(&g_failed);

                    // Add thumbnails to collages (protected section)
                    EnterCriticalSection(&g_thumbCS);
                    srcThumbs.addImage(src);
                    dstThumbs.addImage(edges);
                    LeaveCriticalSection(&g_thumbCS);
                }
                catch (const std::exception& e) {
                    InterlockedIncrement(&g_failed);
                    std::cerr << "[Worker] Error on image #" << i << ": " << e.what() << "\n";
                }
                catch (...) {
                    InterlockedIncrement(&g_failed);
                    std::cerr << "[Worker] Unknown error on image #" << i << "\n";
                }
                });
        }

        // Block until all worker threads finish
        pool.waitAll();
    }

    DeleteCriticalSection(&g_thumbCS);

    // Build and save thumbnail collages
    cv::Mat collageSrc = srcThumbs.buildCollage();
    cv::Mat collageDst = dstThumbs.buildCollage();

    if (!collageSrc.empty()) writer.saveCollage(collageSrc, "_collage_source.jpg");
    if (!collageDst.empty()) writer.saveCollage(collageDst, "_collage_edges.jpg");

    // Summary: total / success / failure / elapsed time
    auto   tEnd = std::chrono::steady_clock::now();
    double elapsed = std::chrono::duration<double>(tEnd - tStart).count();

    std::cout << "[Main] Done. Total: " << loader.count()
              << ", succeeded: " << g_success
              << ", failed: " << g_failed
              << ", time: " << elapsed << " s\n";
    
    return 0;
}

