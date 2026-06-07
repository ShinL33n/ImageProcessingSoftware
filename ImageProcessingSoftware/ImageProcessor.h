#pragma once
#include <opencv2/core/core.hpp>

/// Performs edge detection on a single image.
/// Pipeline: grayscale conversion -> Gaussian blur (noise reduction) -> Canny edge detection
class ImageProcessor {
public:
    /// Canny thresholds - sensible defaults for general-purpose edge detection
    ImageProcessor(double thresh1 = 80.0, double thresh2 = 200.0);

    /// Returns an edge-detected version of the input image (8-bit grayscale).
    cv::Mat process(const cv::Mat& src) const;

private:
    double m_thresh1;
    double m_thresh2;
};
