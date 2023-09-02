#pragma once

#include <cstdint>

#include "Image.h"

class Dither {
public:
	Dither() {};
	~Dither() {};

	//static void Init();

	//static uint8_t BayerDither(const uint8_t value, const int x, const int y, const int factor, const int fromMax, const int toMax);

	//static uint8_t BlueNoiseDither(const uint8_t value, const int x, const int y, const int factor, const int fromMax, const int toMax);

	static bool SaveBayer();

	static bool LoadThreshold(const char* file) { return Dither::ThresholdMap.Read(file, 1); };

	static uint8_t Run(const uint8_t value, const int x, const int y, const int factor, const int fromMax, const int toMax);
	
private:
	static const unsigned int BayerThreshold[];

	static Image ThresholdMap;

	//static Image BlueNoiseThreshold;
};
