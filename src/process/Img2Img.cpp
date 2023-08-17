#include <cmath>

#include "Img2Img.h"

#include "../image/Image.h"
#include "../image/Dither.h"

void Img2Img::Run(const std::string baseImg, const std::string hiddenImg, const std::string significantBitsImg, const int significantBits, const bool repeat, const bool dithered, const std::string outputImg) {
	Image base(baseImg.c_str(), 3);
	Image hidden(hiddenImg.c_str(), 3);

	Image output = base;

	uint8_t bitMask = 0;
	for (int i = 0; i < (int)significantBits; i++) {
		bitMask = bitMask | (0b1 << i);
	}
	int shiftRight = 8 - significantBits;

	for (int x = 0; x < base.GetWidth(); x++) {
		if (!repeat && x >= hidden.GetWidth()) break;

		int hiddenX = repeat ? x % hidden.GetWidth() : x;

		for (int y = 0; y < base.GetHeight(); y++) {
			if (!repeat && y >= hidden.GetHeight()) break;

			int hiddenY = repeat ? y % hidden.GetHeight() : y;

			size_t baseIndex = Img2Img::GetIndex(x, y, base.GetWidth(), 3);
			size_t hiddenIndex = Img2Img::GetIndex(hiddenX, hiddenY, hidden.GetWidth(), 3);
			
			for (size_t i = 0; i < 3; i++) {
				uint8_t baseData = base.GetData(baseIndex + i) & (~bitMask);

				if (dithered) {
					// do nothing for now
					uint8_t hiddenData = Dither::BayerDither(hidden.GetData(hiddenIndex + i), x, y, (int)bitMask, 255, (int)bitMask);

					output.SetData(baseIndex + i, baseData | hiddenData);
				}
				else {
					uint8_t hiddenData = (hidden.GetData(hiddenIndex + i) >> shiftRight) & bitMask;

					output.SetData(baseIndex + i, baseData | hiddenData);
				}
			}
		}
	}

	Image lsb = output;

	for (size_t i = 0; i < lsb.GetSize(); i++) {
		uint8_t data = lsb.GetData(i) & bitMask;

		data = (uint8_t)std::roundf((255.f / (float)bitMask) * (float)data);
		lsb.SetData(i, data);
	}

	output.Write(outputImg.c_str());

	lsb.Write(significantBitsImg.c_str());
}

size_t Img2Img::GetIndex(const int x, const int y, const int w, const int channels) {
	return (size_t)((x + y * w) * channels);
}
