#pragma once
#include <vector>
#include <opencv2/core/core.hpp>

/// Collects images and arranges them into a grid (mosaic/collage).
/// Each thumbnail is resized to thumbSize with black padding to preserve aspect ratio.
class ThumbnailBuilder {
public:
    /// thumbSize: size of each cell in the collage, columns: grid width in cells
    ThumbnailBuilder(cv::Size thumbSize = cv::Size(160, 120), int columns = 8);

    void addImage(const cv::Mat& img);

    /// Returns the assembled collage as a single Mat. Returns empty Mat if no images.
    cv::Mat buildCollage() const;

private:
    /// Resizes image to fit inside thumbSize, padding remainder with black (letterbox).
    static cv::Mat resizeKeepAR(const cv::Mat& img, cv::Size target);

    cv::Size              m_thumbSize;
    int                   m_columns;
    std::vector<cv::Mat>  m_thumbs;
};
