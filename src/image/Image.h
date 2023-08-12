#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>

/// <summary>
/// Basic implementation
/// </summary>
class Image {
public:
    // TODO: Fix LNK1120 Link error
    Image(const char* file, const int forceChannels = 0);
    Image(const Image& other);
    ~Image();

    Image operator=(const Image& other);

    bool Read(const char* file, const int forceChannels = 0);
    bool Write(const char* file);

    inline int GetChannels() const { return m_channels; };
    inline size_t GetSize() const { return m_size; };

public:
    enum class ImageType {
        PNG, JPG, BMP, TGA, NA
    };

private:
    uint8_t* m_data;
    size_t m_size = 0;
    int m_w, m_h, m_channels;

    ImageType GetFileType(const char* file);
};

#endif // !IMAGE_H