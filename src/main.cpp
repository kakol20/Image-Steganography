// Image Steganography.cpp : Defines the entry point for the application.
//

#include "main.h"

int main() {
	// Read settings.json

	std::ifstream f("settings.json");
	json data = json::parse(f);

	std::string input = data["in"];
	std::string output = data["out"];
	unsigned int significantBit = data["significant_bits"];
	bool repeat = data["repeat"];

	// read original image
	//Image inputImg = Image(input.c_str(), 3);
	Image inputImh(input.c_str(), 3);

	std::cin.ignore();
	return 0;
}