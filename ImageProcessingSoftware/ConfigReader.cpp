using namespace std;
#include "ConfigReader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>


static string trim(const string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    size_t b = s.find_last_not_of(" \t\r\n");
    return (a == string::npos) ? "" : s.substr(a, b - a + 1);
}

bool ConfigReader::load(const string& iniPath) {
    ifstream file(iniPath);
    if (!file.is_open()) {
        cerr << "[ConfigReader] Cannot open: " << iniPath << "\n";
        return false;
    }

    string line;
    while (getline(file, line)) {
        line = trim(line);
        // Skip comments and section headers
        if (line.empty() || line[0] == ';' || line[0] == '#' || line[0] == '[')
            continue;

        auto eq = line.find('=');
        if (eq == string::npos) continue;

        string key = trim(line.substr(0, eq));
        string value = trim(line.substr(eq + 1));

        if (key == "source")      sourcePath = value;
        else if (key == "destination") destPath = value;
        else if (key == "threads")     threadCount = stoi(value);
    }

    if (sourcePath.empty() || destPath.empty()) {
        cerr << "[ConfigReader] Missing 'source' or 'destination' key.\n";
        return false;
    }
    return true;
}
