#include "Text2Img.h"

#include <cmath>

#include "../image/Image.h"

void Text2Img::Run(const std::string in, const std::string out, const std::string significantBitsImg, const int significantBits, const bool repeat, const std::string text) {

	Image inputImg(in.c_str(), 3);

	Image outputImg = inputImg;
	Image sigBits = inputImg;
	//sigBits.Clear();

	size_t imageIndex = 0;
	size_t dataIndex = 0;

	uint8_t bitMask = 0;
	for (int i = 0; i < (int)significantBits; i++) {
		bitMask = bitMask | (0b1 << i);
	}

	// generate steganography image
	while (imageIndex < inputImg.GetSize()) {
		if (dataIndex == text.size() && !repeat) break;

		dataIndex = dataIndex % text.size();

		uint8_t character = (uint8_t)text[dataIndex];
		size_t bitSize = sizeof(char) * 8;

		for (int i = (int)bitSize - 1; i >= 0; i -= (int)significantBits) {
			if (imageIndex == inputImg.GetSize()) break;

			int bitshift = i - (significantBits - 1);

			uint8_t bits = (bitMask << bitshift) & character;
			bits = bits >> bitshift;

			uint8_t imageData = inputImg.GetData(imageIndex);
			imageData = (imageData & (~bitMask)) | bits;

			inputImg.SetData(imageIndex, imageData);

			imageIndex++;
		}

		dataIndex++;
	}
	
	// generate least significant bits image

	for (size_t i = 0; i < inputImg.GetSize(); i++) {
		uint8_t leastSignificantBits = (uint8_t)std::roundf((255.f / (float)bitMask) * (float)(inputImg.GetData(i) & bitMask));

		sigBits.SetData(i, leastSignificantBits);
	}

	outputImg.Write(out.c_str());
	sigBits.Write(significantBitsImg.c_str());
}
