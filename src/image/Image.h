#pragma once

#include <cstdint>

/// <summary>
/// Basic implementation
/// </summary>
class Image {
public:
	Image(const char* file, const int forceChannels = -1);
	Image(const Image& other);
	~Image();

	Image operator=(const Image& other);

	bool Read(const char* file, const int forceChannels = -1);
	bool Write(const char* file);

	inline int GetChannels() const { return m_channels; };
	inline size_t GetSize() const { return m_size; };

public:
	enum class ImageType {
		PNG, JPG, BMP, TGA, NA
	};

private:
	uint8_t* m_data = NULL;
	size_t m_size = 0;
	int m_w, m_h, m_channels;

	ImageType GetFileType(const char* file);
};