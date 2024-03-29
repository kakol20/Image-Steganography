#include "Dither.h"

#include <cmath>

const unsigned int Dither::BayerThreshold[] = {
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
//Image Dither::BlueNoiseThreshold = Image("img/LDR_LLL1_0.png", 1);

//void Dither::Init() {
//	Dither::BlueNoiseThreshold = Image("img/LDR_LLL1_0.png", 1);
//}

Image Dither::ThresholdMap;

//uint8_t Dither::BayerDither(const uint8_t value, const int x, const int y, const int factor, const int fromMax, const int toMax) {
//	float threshold = (float)Dither::BayerThreshold[(x % 16) + (y % 16) * 16] / 256.f;
//	float octet = 1.f / (float)factor;
//
//	float v = (float)value / (float)fromMax;
//	v = v + octet * (threshold - 0.5f);
//	v = std::roundf(v * (float)factor) / (float)factor;
//
//	// clamp
//
//	v = v > 1.f ? 1.f : v;
//	v = v < 0.f ? 0.f : v;
//
//	v *= (float)toMax;
//
//	return (uint8_t)std::roundf(v);
//}

//uint8_t Dither::BlueNoiseDither(const uint8_t value, const int x, const int y, const int factor, const int fromMax, const int toMax) {
//	//float threshold = (float)Dither::BayerThreshold[(x % 16) + (y % 16) * 16] / 256.f;
//	float threshold = (float)Dither::BlueNoiseThreshold.GetData((size_t)((x % 64) + (y % 64) * 64)) / 256.f;
//	float octet = 1.f / (float)factor;
//
//	float v = (float)value / (float)fromMax;
//	v = v + octet * (threshold - 0.5f);
//	v = std::roundf(v * (float)factor) / (float)factor;
//
//	// clamp
//
//	v = v > 1.f ? 1.f : v;
//	v = v < 0.f ? 0.f : v;
//
//	v *= (float)toMax;
//
//	return (uint8_t)std::roundf(v);
//}

bool Dither::SaveBayer() {
	Image bayer(16, 16, 1);

	for (size_t i = 0; i < (size_t)16 * 16; i++) {
		bayer.SetData(i, Dither::BayerThreshold[i]);
	}

	return bayer.Write("data/bayer.png");
}

uint8_t Dither::Run(const uint8_t value, const int x, const int y, const int factor, const int fromMax, const int toMax) {

	//if (!ditherMapIMG.Read(ditherMap, 1)) return -1;

	int l_x = x % Dither::ThresholdMap.GetWidth();
	int l_y = y % Dither::ThresholdMap.GetHeight();
	size_t index = (size_t)(l_x + l_y * Dither::ThresholdMap.GetWidth());

	uint8_t data = Dither::ThresholdMap.GetData(index);
	float threshold = (float)data / 256.f;

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