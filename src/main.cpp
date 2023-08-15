// Image Steganography.cpp : Defines the entry point for the application.
//

#include "main.h"

int main(int argc, char* argv[]) {
	// Read settings.json

	std::ifstream f("settings.json");
	json settings = json::parse(f, nullptr, true, true);

	/*bool repeat = settings["repeat"];
	std::string dataInput = settings["text"];
	std::string input = settings["in"];
	std::string output = settings["out"];
	std::string sigBitImg = settings["significant_bits_img"];
	unsigned int significantBits = settings["significant_bits"];*/

	std::string process = settings["process"];

	if (process == "text2img") {
		Text2Img::Run(settings["text2img"]["in"],
			settings["text2img"]["out"],
			settings["text2img"]["significant_bits_img"],
			settings["text2img"]["significant_bits"],
			settings["text2img"]["repeat"],
			settings["text2img"]["text"]);
	}

	std::cout << "Press enter to exit...\n";
	std::cin.ignore();
	return 0;
}

#ifdef USE_MAP
float Map(const float val, const float fromMin, const float fromMax, const float toMin, const float toMax) {
	float factor = (val - fromMin) / (fromMax - fromMin);
	float lerp = ((toMax - toMin) * factor) + toMin;
	float out = lerp > toMax ? toMax : lerp;
	return out < toMin ? toMin : out;
}
#endif // USE_MAP