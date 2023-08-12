#include "Image.h"

#include <iostream>
#include <cstring>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "../../ext/stb/stb_image.h"
#include "../../ext/stb/stb_image_write.h"

Image::Image(const char* file, const int forceChannels) {

	if (!Image::Read(file, forceChannels)) {
		std::cout << "Read failed " << file << '\n';
	}
	else {
		std::cout << "Read success " << file << '\n';
	}
}

Image::Image(const Image& other) {
	//stbi_image_free(m_data);

	m_w = other.m_w;
	m_h = other.m_h;
	m_channels = other.m_channels;
	m_size = other.m_size;

	m_data = new uint8_t[m_size];

	memcpy(m_data, other.m_data, m_size);
}

Image::~Image() {
	stbi_image_free(m_data);
}

Image Image::operator=(const Image& other) {
	if (&other == this) return *this;

	stbi_image_free(m_data);

	m_w = other.m_w;
	m_h = other.m_h;
	m_channels = other.m_channels;
	m_size = other.m_size;

	m_data = new uint8_t[m_size];

	memcpy(m_data, other.m_data, m_size);

	return *this;
}

bool Image::Read(const char* file, const int forceChannels) {
	if (forceChannels > 0 && forceChannels <= 4) {
		m_data = stbi_load(file, &m_w, &m_h, &m_channels, forceChannels);
	}
	else {
		m_data = stbi_load(file, &m_w, &m_h, &m_channels, 0);
	}

	m_size = (size_t)(m_w * m_h * m_channels);

	return m_data != NULL;
}

bool Image::Write(const char* file) {
	ImageType type = GetFileType(file);
	int success = 0;

	switch (type) {
	case Image::ImageType::PNG:
		success = stbi_write_png(file, m_w, m_h, m_channels, m_data, m_w * m_channels);
		break;
	case Image::ImageType::JPG:
		success = stbi_write_jpg(file, m_w, m_h, m_channels, m_data, 100);
		break;
	case Image::ImageType::BMP:
		success = stbi_write_bmp(file, m_w, m_h, m_channels, m_data);
		break;
	case Image::ImageType::TGA:
		success = stbi_write_tga(file, m_w, m_h, m_channels, m_data);
		break;
	case Image::ImageType::NA:
		std::cout << "File type not supported\nPNG, JPG, BMP or TGA";
		success = 0;
		break;
	default:
		std::cout << "File type not supported\nPNG, JPG, BMP or TGA";
		success = 0;
		break;
	}

	if (success != 0) {
		std::cout << "Write success " << file << '\n';
	}
	else {
		std::cout << "Write fail " << file << '\n';
	}

	return success != 0;
}

Image::ImageType Image::GetFileType(const char* file) {
	const char* ext = strrchr(file, '.');

	if (ext != nullptr) {
		if (strcmp(ext, ".png") == 0) {
			return ImageType::PNG;
		}
		else if (strcmp(ext, ".jpg") == 0) {
			return ImageType::JPG;
		}
		else if (strcmp(ext, ".bmp") == 0) {
			return ImageType::BMP;
		}
		else if (strcmp(ext, ".tga") == 0) {
			return ImageType::TGA;
		}
	}

	return ImageType::NA;
}