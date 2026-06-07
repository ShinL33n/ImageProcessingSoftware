#include "ThumbnailBuilder.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>

ThumbnailBuilder::ThumbnailBuilder(cv::Size thumbSize, int columns)
    : m_thumbSize(thumbSize), m_columns(columns) {
}

void ThumbnailBuilder::addImage(const cv::Mat& img) {
    if (!img.empty())
        m_thumbs.push_back(resizeKeepAR(img, m_thumbSize));
}

cv::Mat ThumbnailBuilder::resizeKeepAR(const cv::Mat& img, cv::Size target) {
    // Compute scale that fits the image inside target without cropping
    double scaleX = (double)target.width / img.cols;
    double scaleY = (double)target.height / img.rows;
    double scale = std::min(scaleX, scaleY);

    int newW = (int)(img.cols * scale);
    int newH = (int)(img.rows * scale);

    cv::Mat resized;
    cv::resize(img, resized, cv::Size(newW, newH));

    // Place resized image on a black canvas (letterbox/pillarbox)
    cv::Mat canvas(target, resized.type(), cv::Scalar(0, 0, 0));
    int offX = (target.width - newW) / 2;
    int offY = (target.height - newH) / 2;
    resized.copyTo(canvas(cv::Rect(offX, offY, newW, newH)));
    return canvas;
}

cv::Mat ThumbnailBuilder::buildCollage() const {
    if (m_thumbs.empty()) return cv::Mat();

    int rows = (int)std::ceil((double)m_thumbs.size() / m_columns);
    int cols = std::min((int)m_thumbs.size(), m_columns);

    // Determine channel count from first thumbnail
    int type = m_thumbs[0].type();
    cv::Mat collage(rows * m_thumbSize.height, cols * m_thumbSize.width, type, cv::Scalar::all(0));

    for (size_t i = 0; i < m_thumbs.size(); ++i) {
        int row = (int)i / m_columns;
        int col = (int)i % m_columns;
        int x = col * m_thumbSize.width;
        int y = row * m_thumbSize.height;
        m_thumbs[i].copyTo(collage(cv::Rect(x, y, m_thumbSize.width, m_thumbSize.height)));
    }
    return collage;
}
