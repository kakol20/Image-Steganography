#pragma once

#include <string>

class Text2Img {
public:
	Text2Img() {};
	~Text2Img() {};

	static void Run(const std::string in, const std::string out, const std::string significantBitsImg, const int significantBits, const bool repeat, const std::string textFile);
};
