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
};

#endif // !IMG2IMG_H
