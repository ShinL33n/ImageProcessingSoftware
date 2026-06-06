using namespace std;
#include <iostream>
#include <string>
#include <windows.h>

#include "ConfigReader.h"
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
}

