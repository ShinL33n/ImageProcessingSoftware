#include "ImageProcessor.h"
#include <opencv2/imgproc/imgproc.hpp>

ImageProcessor::ImageProcessor(double thresh1, double thresh2)
    : m_thresh1(thresh1), m_thresh2(thresh2) {
}

cv::Mat ImageProcessor::process(const cv::Mat& src) const {
    cv::Mat gray, blurred, edges;

    // Step 1: Convert to grayscale (Canny requires single-channel input)
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

    // Step 2: Gaussian blur to reduce noise before edge detection
    cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 1.4);

    // Step 3: Canny edge detection
    cv::Canny(blurred, edges, m_thresh1, m_thresh2);

    return edges;
}
