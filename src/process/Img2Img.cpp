#include <cmath>

#include "Img2Img.h"

#include "../image/Image.h"
#include "../image/Dither.h"

void Img2Img::Run(const std::string baseImg, const std::string hiddenImg, const std::string significantBitsImg, const int significantBits, const bool repeat, const bool dithered, const std::string outputImg, const std::string ditherMap) {
	//Image base(baseImg.c_str(), 3);
	//Image hidden(hiddenImg.c_str(), 3);

	Image base;
	if (!base.Read(baseImg.c_str())) return;

	const int channels = base.GetChannels();

	Image hidden;
	if (!hidden.Read(hiddenImg.c_str(), channels)) return;

	if (!Dither::LoadThreshold(ditherMap.c_str())) return;

	Image output = base;

	Image lsb = output;

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

			size_t baseIndex = Img2Img::GetIndex(x, y, base.GetWidth(), channels);
			size_t hiddenIndex = Img2Img::GetIndex(hiddenX, hiddenY, hidden.GetWidth(), channels);

			for (size_t i = 0; i < channels; i++) {
				uint8_t baseData = base.GetData(baseIndex + i) & (~bitMask);

				uint8_t hiddenData = 0;

				if (dithered) {
					// do nothing for now
					//uint8_t hiddenData = Dither::BlueNoiseDither(hidden.GetData(hiddenIndex + i), x, y, (int)bitMask, 255, (int)bitMask);
					hiddenData = Dither::Run(hidden.GetData(hiddenIndex + i), x, y, (int)bitMask, 255, (int)bitMask);

					output.SetData(baseIndex + i, baseData | hiddenData);
				}
				else {
					hiddenData = (hidden.GetData(hiddenIndex + i) >> shiftRight) & bitMask;

					output.SetData(baseIndex + i, baseData | hiddenData);
				}

				lsb.SetData(baseIndex + i, uint8_t((255 * (int)hiddenData) / (int)bitMask));
			}
		}
	}

	output.Write(outputImg.c_str());

	lsb.Write(significantBitsImg.c_str());
}

size_t Img2Img::GetIndex(const int x, const int y, const int w, const int channels) {
	return (size_t)((x + y * w) * channels);
}