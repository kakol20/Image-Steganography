// Image Steganography.cpp : Defines the entry point for the application.
//

#include "main.h"

int main(int argc, char* argv[]) {
	// Read settings.json

	std::ifstream f("settings.json");
	json data = json::parse(f);

	std::string input = data["in"];
	std::string output = data["out"];
	unsigned int significantBit = data["significant_bits"];
	bool repeat = data["repeat"];

	// read original image
	//Image inputImg = Image(input.c_str(), 3);
	Image inputImg(input.c_str(), 3);

	Image outputImg = inputImg;
	Image sigBits = inputImg;

	outputImg.Write(output.c_str());
	sigBits.Write("img/significantBits.png");

	std::cout << "Press enter to exit...\n";
	std::cin.ignore();
	return 0;
}