#include "Img2Img.h"

#include "../image/Image.h"

void Img2Img::Run(const std::string baseImg, const std::string hiddenImg, const std::string significantBitsImg, const int significantBits, const bool repeat, const bool dithered, const std::string outputImg) {
	Image base(baseImg.c_str(), 3);
	Image hidden(hiddenImg.c_str(), 3);

	Image output = base;

	output.Write(outputImg.c_str());
}
