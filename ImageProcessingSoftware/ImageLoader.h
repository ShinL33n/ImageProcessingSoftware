#pragma once
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>

/// Scans a directory for supported image files and loads them on demand.
/// Supported extensions: jpg, jpeg, png, bmp, tiff, tif
class ImageLoader {
public:
    explicit ImageLoader(const std::string& folderPath);

    /// Returns list of found image file paths.
    const std::vector<std::string>& filePaths() const { return m_paths; }

    /// Loads image at given index. Returns empty Mat on failure.
    cv::Mat loadAt(size_t index) const;

    size_t count() const { return m_paths.size(); }

private:
    std::vector<std::string> m_paths;

    static bool isSupportedExtension(const std::string& path);
};
