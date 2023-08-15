#ifndef IMG2IMG_H
#define IMG2IMG_H

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

	static uint8_t Dither(const uint8_t value, const int x, const int y, const int factor, const int fromMax, const int toMax);
	
	static const unsigned int Threshold[];
};

#endif // !IMG2IMG_H
