#pragma once

#include <string>

class Img2Img {
public:
	Img2Img() {};
	~Img2Img() {};

	static void Run(const std::string baseImg,
		const std::string hiddenImg,
		const std::string significantBitsImg,
		const int significantBits,
		const bool repeat,
		const bool dithered,
		const std::string outputImg);

private:
	static size_t GetIndex(const int x, const int y, const int w, const int channels);
};
