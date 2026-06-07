#include "ImageLoader.h"
#include <opencv2/highgui/highgui.hpp>
#include <windows.h>
#include <algorithm>
#include <iostream>

static std::string toLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

bool ImageLoader::isSupportedExtension(const std::string& path) {
    static const std::vector<std::string> exts = { ".jpg",".jpeg",".png",".bmp",".tiff",".tif" };
    size_t dot = path.rfind('.');
    if (dot == std::string::npos) return false;
    std::string ext = toLower(path.substr(dot));
    return std::find(exts.begin(), exts.end(), ext) != exts.end();
}

ImageLoader::ImageLoader(const std::string& folderPath) {
    // Use Windows API to enumerate files in directory
    std::string pattern = folderPath + "\\*";
    WIN32_FIND_DATAA fd;
    HANDLE h = FindFirstFileA(pattern.c_str(), &fd);
    if (h == INVALID_HANDLE_VALUE) {
        std::cerr << "[ImageLoader] Cannot open folder: " << folderPath << "\n";
        return;
    }
    do {
        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;
        std::string name = fd.cFileName;
        if (isSupportedExtension(name))
            m_paths.push_back(folderPath + "\\" + name);
    } while (FindNextFileA(h, &fd));
    FindClose(h);

    std::sort(m_paths.begin(), m_paths.end());
    std::cout << "[ImageLoader] Found " << m_paths.size() << " image(s).\n";
}

cv::Mat ImageLoader::loadAt(size_t index) const {
    cv::Mat img = cv::imread(m_paths[index], cv::IMREAD_COLOR);
    if (img.empty())
        std::cerr << "[ImageLoader] Failed to load: " << m_paths[index] << "\n";
    return img;
}
