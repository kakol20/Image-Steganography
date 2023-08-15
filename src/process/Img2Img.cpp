#include <cmath>

#include "Img2Img.h"

const unsigned int Img2Img::Threshold[] = {
	  0, 192,  48, 240,  12, 204,  60, 252,   3, 195,  51, 243,  15, 207,  63, 255,
	128,  64, 176, 112, 140,  76, 188, 124, 131,  67, 179, 115, 143,  79, 191, 127,
	 32, 224,  16, 208,  44, 236,  28, 220,  35, 227,  19, 211,  47, 239,  31, 223,
	160,  96, 144,  80, 172, 108, 156,  92, 163,  99, 147,  83, 175, 111, 159,  95,
	  8, 200,  56, 248,   4, 196,  52, 244,  11, 203,  59, 251,   7, 199,  55, 247,
	136,  72, 184, 120, 132,  68, 180, 116, 139,  75, 187, 123, 135,  71, 183, 119,
	 40, 232,  24, 216,  36, 228,  20, 212,  43, 235,  27, 219,  39, 231,  23, 215,
	168, 104, 152,  88, 164, 100, 148,  84, 171, 107, 155,  91, 167, 103, 151,  87,
	  2, 194,  50, 242,  14, 206,  62, 254,   1, 193,  49, 241,  13, 205,  61, 253,
	130,  66, 178, 114, 142,  78, 190, 126, 129,  65, 177, 113, 141,  77, 189, 125,
	 34, 226,  18, 210,  46, 238,  30, 222,  33, 225,  17, 209,  45, 237,  29, 221,
	162,  98, 146,  82, 174, 110, 158,  94, 161,  97, 145,  81, 173, 109, 157,  93,
	 10, 202,  58, 250,   6, 198,  54, 246,   9, 201,  57, 249,   5, 197,  53, 245,
	138,  74, 186, 122, 134,  70, 182, 118, 137,  73, 185, 121, 133,  69, 181, 117,
	 42, 234,  26, 218,  38, 230,  22, 214,  41, 233,  25, 217,  37, 229,  21, 213,
	170, 106, 154,  90, 166, 102, 150,  86, 169, 105, 153,  89, 165, 101, 149,  85
};

#include "../image/Image.h"

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
					uint8_t hiddenData = Img2Img::Dither(hidden.GetData(hiddenIndex + i), x, y, (int)bitMask, 255, (int)bitMask);
					uint8_t lsbData = Img2Img::Dither(hidden.GetData(hiddenIndex + i), x, y, (int)bitMask, 255, 255);

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

uint8_t Img2Img::Dither(const uint8_t value, const int x, const int y, const int factor, const int fromMax, const int toMax) {
	float threshold = (float)Img2Img::Threshold[(x % 16) + (y % 16) * 16] / 256.f;
	float octet = 1.f / (float)factor;

	float v = (float)value / (float)fromMax;
	v = v + octet * (threshold - 0.5f);
	v = std::roundf(v * (float)factor) / (float)factor;

	// clamp

	v = v > 1.f ? 1.f : v;
	v = v < 0.f ? 0.f : v;

	v *= (float)toMax;

	return (uint8_t)std::roundf(v);
}
