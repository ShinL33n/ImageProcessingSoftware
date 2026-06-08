#pragma once
#include <string>

/// Reads source/destination paths, worker thread count and thumbnail
/// settings from a .ini file.
///
/// Expected INI format:
///   [paths]
///   source=C:\input
///   destination=C:\output
///   [settings]
///   threads=0            ; 0 = auto (number of logical CPU cores)
///   [thumbnail]
///   width=160
///   height=120
///   columns=8
class ConfigReader {
public:
    std::string sourcePath;
    std::string destPath;
    int         threadCount = 0;   ///< 0 = auto-detect logical cores (resolved in load())

    // Thumbnail / collage settings - configurable per requirement
    int         thumbWidth = 160;
    int         thumbHeight = 120;
    int         thumbColumns = 8;

    /// Opens and parses the INI file.
    /// Resolves threadCount to the number of logical cores when set to <= 0.
    /// Returns false if file cannot be opened or required keys are missing.
    bool load(const std::string& iniPath);
};
