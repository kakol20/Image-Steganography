#include "Img2Img.h"

#include "../image/Image.h"

void Img2Img::Run(const std::string baseImg, const std::string hiddenImg, const std::string significantBitsImg, const int significantBits, const bool repeat, const bool dithered, const std::string outputImg) {
	Image base(baseImg.c_str(), 3);
	Image hidden(hiddenImg.c_str(), 3);

	Image output = base;

	for (int x = 0; x < base.GetWidth(); x++) {
		if (!repeat && x >= hidden.GetWidth()) break;

		int hiddenX = repeat ? x % hidden.GetWidth() : x;

		for (int y = 0; y < base.GetHeight(); y++) {
			if (!repeat && y >= hidden.GetHeight()) break;

			int hiddenY = repeat ? y % hidden.GetHeight() : y;

			size_t baseIndex = Img2Img::GetIndex(x, y, base.GetWidth(), 3);
			size_t hiddenIndex = Img2Img::GetIndex(hiddenX, hiddenY, hidden.GetWidth(), 3);

			output.SetData(baseIndex + 0, hidden.GetData(hiddenIndex + 0));
			output.SetData(baseIndex + 1, hidden.GetData(hiddenIndex + 1));
			output.SetData(baseIndex + 2, hidden.GetData(hiddenIndex + 2));
		}
	}

	output.Write(outputImg.c_str());

	Image lsb = output;
	lsb.Write(significantBitsImg.c_str());
}

size_t Img2Img::GetIndex(const int x, const int y, const int w, const int channels) {
	return (size_t)((x + y * w) * channels);
}
