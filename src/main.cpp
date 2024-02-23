// Image Steganography.cpp : Defines the entry point for the application.
//

#include "main.h"

int main(int argc, char* argv[]) {
	// Read settings.json

	std::ifstream f("settings.json");

	if (f) {
		json settings = json::parse(f);

		auto& processes = settings["process"];

		for (size_t i = 0; i < processes.size(); i++) {
			auto& runSettings = processes[i];
			std::string process = runSettings["type"];

			if (process == "img2img") {
				Img2Img::Run(runSettings["baseImg"],
					runSettings["hiddenImg"],
					runSettings["significant_bits_img"],
					runSettings["significant_bits"],
					runSettings["repeat"],
					runSettings["dithered"],
					runSettings["output"],
					runSettings["dither_map"]);
			}
			else if (process == "text2img") {
				Text2Img::Run(runSettings["in"],
					runSettings["out"],
					runSettings["significant_bits_img"],
					runSettings["significant_bits"],
					runSettings["repeat"],
					runSettings["text"]);
			}

			Log::EndLine();
		}
		Log::Save(settings["overwrite_log"]);
	}
	else {
		Log::StartLine();
		Log::Write("settings.json not found");
		Log::EndLine();
		Log::Save(true);
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