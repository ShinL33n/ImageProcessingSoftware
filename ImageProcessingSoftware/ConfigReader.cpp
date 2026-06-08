#include "ConfigReader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <thread>   // std::thread::hardware_concurrency

static std::string trim(const std::string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    size_t b = s.find_last_not_of(" \t\r\n");
    return (a == std::string::npos) ? "" : s.substr(a, b - a + 1);
}

// Safe string -> int conversion. Returns the fallback on malformed input
// instead of throwing (std::stoi throws on non-numeric values, which would
// otherwise crash the program on a bad config file).
static int toInt(const std::string& s, int fallback) {
    try {
        return std::stoi(s);
    }
    catch (...) {
        return fallback;
    }
}

bool ConfigReader::load(const std::string& iniPath) {
    std::ifstream file(iniPath);
    if (!file.is_open()) {
        std::cerr << "[ConfigReader] Cannot open: " << iniPath << "\n";
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        line = trim(line);
        // Skip empty lines, comments and section headers
        if (line.empty() || line[0] == ';' || line[0] == '#' || line[0] == '[')
            continue;

        auto eq = line.find('=');
        if (eq == std::string::npos) continue;

        std::string key = trim(line.substr(0, eq));
        std::string value = trim(line.substr(eq + 1));

        if (key == "source")      sourcePath = value;
        else if (key == "destination") destPath = value;
        else if (key == "threads")     threadCount = toInt(value, threadCount);
        else if (key == "width")       thumbWidth = toInt(value, thumbWidth);
        else if (key == "height")      thumbHeight = toInt(value, thumbHeight);
        else if (key == "columns")     thumbColumns = toInt(value, thumbColumns);
    }

    if (sourcePath.empty() || destPath.empty()) {
        std::cerr << "[ConfigReader] Missing 'source' or 'destination' key.\n";
        return false;
    }

    // Default thread count = number of logical CPU cores (requirement).
    if (threadCount <= 0) {
        unsigned int hc = std::thread::hardware_concurrency();
        threadCount = (hc > 0) ? static_cast<int>(hc) : 4; // fallback if undetectable
    }

    // Guard against nonsensical thumbnail values
    if (thumbWidth <= 0) thumbWidth = 160;
    if (thumbHeight <= 0) thumbHeight = 120;
    if (thumbColumns <= 0) thumbColumns = 8;

    return true;
}
