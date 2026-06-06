using namespace std;
#include "ResultWriter.h"
#include <opencv2/highgui/highgui.hpp>
#include <windows.h>
#include <iostream>

ResultWriter::ResultWriter(const string& destPath) : m_destPath(destPath) {
    // Create destination directory (and any needed parents) if missing
    if (!CreateDirectoryA(destPath.c_str(), NULL) &&
        GetLastError() != ERROR_ALREADY_EXISTS) {
        cerr << "[ResultWriter] Cannot create directory: " << destPath << "\n";
    }
}

bool ResultWriter::saveImage(const cv::Mat& img, const string& filename) const {
    string outPath = m_destPath + "\\" + filename;
    bool ok = cv::imwrite(outPath, img);
    if (!ok) cerr << "[ResultWriter] Failed to save: " << outPath << "\n";
    return ok;
}

bool ResultWriter::saveCollage(const cv::Mat& collage, const string& filename) const {
    return saveImage(collage, filename);
}
