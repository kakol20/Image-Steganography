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
		auto& runSettings = settings[process.c_str()];
		Text2Img::Run(runSettings["in"],
			runSettings["out"],
			runSettings["significant_bits_img"],
			runSettings["significant_bits"],
			runSettings["repeat"],
			runSettings["text"]);
	}
	else if (process == "img2img") {
		auto& runSettings = settings[process.c_str()];
		Img2Img::Run(runSettings["baseImg"],
			runSettings["hiddenImg"],
			runSettings["significant_bits_img"],
			runSettings["significant_bits"],
			runSettings["repeat"],
			runSettings["dithered"],
			runSettings["output"]);
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