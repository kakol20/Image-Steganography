#ifndef DITHER_H
#define DITHER_H

#include <cstdint>

#include "Image.h"

class Dither {
public:
	Dither() {};
	~Dither() {};

	//static void Init();

	static uint8_t BayerDither(const uint8_t value, const int x, const int y, const int factor, const int fromMax, const int toMax);

	static uint8_t BlueNoiseDither(const uint8_t value, const int x, const int y, const int factor, const int fromMax, const int toMax);
	
private:
	static const unsigned int BayerThreshold[];

	static Image BlueNoiseThreshold;
};

#endif // !DITHER_H
