#pragma once
using namespace std;
#include <string>

/// Reads source/destination paths and thread count from a .ini file.
/// Expected INI format:
///   [paths]
///   source=C:\images\input
///   destination=C:\images\output
///   [settings]
///   threads=4
class ConfigReader {
public:
    string sourcePath;
    string destPath;
    int         threadCount = 4;

    /// Opens and parses the INI file.
    /// Returns false if file cannot be opened or required keys are missing.
    bool load(const string& iniPath);
};
