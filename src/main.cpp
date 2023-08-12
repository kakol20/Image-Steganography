// Image Steganography.cpp : Defines the entry point for the application.
//

#include "main.h"

int main(int argc, char* argv[]) {
	// Read settings.json

	std::ifstream f("settings.json");
	json settings = json::parse(f);

	std::string input = settings["in"];
	std::string output = settings["out"];
	unsigned int significantBits = settings["significant_bits"];
	std::string sigBitImg = settings["significant_bits_img"];
	bool repeat = settings["repeat"];
	std::string dataInput = settings["text"];

	// read original image
	//Image inputImg = Image(input.c_str(), 3);
	Image inputImg(input.c_str(), 3);

	Image outputImg = inputImg;
	Image sigBits = inputImg;
	sigBits.Clear();

	size_t imageIndex = 0;
	size_t dataIndex = 0;

	uint8_t bitMask = 0;
	for (int i = 0; i < (int)significantBits; i++) {
		bitMask = bitMask | (0b1 << i);
	}

	// generate steganography image
	while (imageIndex < inputImg.GetSize()) {
		if (dataIndex == dataInput.size() && !repeat) break;

		dataIndex = dataIndex % dataInput.size();

		uint8_t character = (uint8_t)dataInput[dataIndex];
		size_t bitSize = sizeof(char) * 8;

		for (int i = (int)bitSize - 1; i >= 0; i -= (int)significantBits) {
			if (imageIndex == inputImg.GetSize()) break;

			int bitshift = i - (significantBits - 1);

			uint8_t bits = (bitMask << bitshift) & character;
			bits = bits >> bitshift;

			uint8_t imageData = inputImg.GetData(imageIndex);
			imageData = (imageData & (~bitMask)) | bits;

			inputImg.SetData(imageIndex, imageData);

			imageIndex++;
		}

		dataIndex++;
	}
	
	// generate least significant bits image

	for (size_t i = 0; i < inputImg.GetSize(); i++) {
		float leastSignificantBits = (float)(inputImg.GetData(i) & bitMask);
		leastSignificantBits = std::roundf(Map(leastSignificantBits, 0.f, (float)bitMask, 0.f, 255.f));

		sigBits.SetData(i, (uint8_t)leastSignificantBits);
	}

	outputImg.Write(output.c_str());
	sigBits.Write("img/leastSignificantBits.png");

	std::cout << "Press enter to exit...\n";
	std::cin.ignore();
	return 0;
}

float Map(const float val, const float fromMin, const float fromMax, const float toMin, const float toMax) {
	float factor = (val - fromMin) / (fromMax - fromMin);
	float lerp = ((toMax - toMin) * factor) + toMin;
	float out = lerp > toMax ? toMax : lerp;
	return out < toMin ? toMin : out;
}
