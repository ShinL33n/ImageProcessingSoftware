using namespace std;
#include <iostream>
#include <string>
#include <windows.h>

#include "ConfigReader.h"
#include "ResultWriter.h"
#include "ImageLoader.h"
#include "ThumbnailBuilder.h"

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
}

