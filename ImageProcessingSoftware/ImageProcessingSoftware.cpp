using namespace std;
#include <iostream>
#include <string>
#include <windows.h>
#include "ImageLoader.h"

#include "ConfigReader.h"
#include "ResultWriter.h"

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
    std:cerr << "[Main] No images found. Exiting \n";
        return 1;
    }

    // Prepare output helpers
    ResultWriter   writer(config.destPath);
}

