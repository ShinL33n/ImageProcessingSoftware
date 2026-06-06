#pragma once
using namespace std;
#include <string>
#include <opencv2/core/core.hpp>

/// Saves processed images and collage files to the destination directory.
/// Creates the destination folder if it does not exist.
class ResultWriter {
public:
    explicit ResultWriter(const string& destPath);

    /// Saves a single processed image. filename is the original base name.
    bool saveImage(const cv::Mat& img, const string& filename) const;

    /// Saves a collage Mat under a fixed name in the destination folder.
    bool saveCollage(const cv::Mat& collage, const string& filename) const;

private:
    string m_destPath;
};
