using namespace std;
#include <iostream>
#include <string>
#include <windows.h>

#include "ConfigReader.h"
#include "ResultWriter.h"
#include "ImageLoader.h"
#include "ThumbnailBuilder.h"
#include "ImageProcessor.h"
#include "ThreadPool.h"

// Mutex protecting access to shared ThumbnailBuilder instances from worker threads
static CRITICAL_SECTION g_thumbCS;

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " config.ini\n";
        return 1;
    }

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
    ResultWriter   writer(config.destPath);
    ThumbnailBuilder srcThumbs(cv::Size(160, 120), 8);
    ThumbnailBuilder dstThumbs(cv::Size(160, 120), 8);

    InitializeCriticalSection(&g_thumbCS);

    // Submit processing tasks to thread pool
    // Each task: load -> process -> save result -> add to collages (thread-safe)
    {
        ThreadPool pool(config.threadCount);
        ImageProcessor processor; // stateless - safe to share across tasks

        for (size_t i = 0; i < loader.count(); ++i) {
            pool.submit([&, i]() {
                // Load original image
                cv::Mat src = loader.loadAt(i);
                if (src.empty()) return;

                // Run edge detection
                cv::Mat edges = processor.process(src);

                // Derive output filename from original path
                std::string srcPath = loader.filePaths()[i];
                size_t slash = srcPath.find_last_of("\\/");
                std::string filename = (slash == std::string::npos) ? srcPath : srcPath.substr(slash + 1);

                // Save processed image
                writer.saveImage(edges, filename);

                // Add thumbnails to collages (protected section)
                EnterCriticalSection(&g_thumbCS);
                srcThumbs.addImage(src);
                dstThumbs.addImage(edges);
                LeaveCriticalSection(&g_thumbCS);
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

    std::cout << "[Main] Done. Processed " << loader.count() << " image(s).\n";
}

