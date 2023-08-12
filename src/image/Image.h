#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>

/// <summary>
/// Basic implementation
/// </summary>
class Image {
public:
	Image(const char* file, const int forceChannels = 0);
	Image(const Image& other);
	~Image();

	Image operator=(const Image& other);

	bool Read(const char* file, const int forceChannels = 0);
	bool Write(const char* file);

	inline int GetChannels() const { return m_channels; };
	inline size_t GetSize() const { return m_size; };

	inline uint8_t GetData(const size_t index) const { return m_data[index]; };
	inline void SetData(const size_t index, const uint8_t data) { m_data[index] = data; };

	void Clear();

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