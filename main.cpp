// Image Steganography.cpp : Defines the entry point for the application.
//

#include "Image Steganography.h"

int main() {
	std::cout << "Hello CMake.\n";

	// Read settings.json

	std::ifstream f("settings.json");
	json data = json::parse(f);

	const std::string input = data["in"];
	const std::string output = data["out"];
	const unsigned int significantBit = data["significant_bits"];
	const bool repeat = data["repeat"];

	//std::cout << input << '\n';

	std::cin.get();
	return 0;
}