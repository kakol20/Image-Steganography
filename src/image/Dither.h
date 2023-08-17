#ifndef DITHER_H
#define DITHER_H

#include <cstdint>

class Dither {
public:
	Dither() {};
	~Dither() {};

	static uint8_t BayerDither(const uint8_t value, const int x, const int y, const int factor, const int fromMax, const int toMax);
	
private:
	static const unsigned int BayerThreshold[];
};

#endif // !DITHER_H
