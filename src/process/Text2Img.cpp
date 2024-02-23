#include "Text2Img.h"

#include <cmath>

#include "../image/Image.h"
#include "../other/Txt.h"

void Text2Img::Run(const std::string in, const std::string out, const std::string significantBitsImg, const int significantBits, const bool repeat, const std::string textFile) {

	Image inputImg;
	if (!inputImg.Read(in.c_str())) return;

	Txt text;
	if (!text.Read(textFile.c_str())) return;

	Image outputImg = inputImg;
	Image sigBits = inputImg;
	//sigBits.Clear();

	size_t imageIndex = 0;
	size_t dataIndex = 0;

	uint8_t bitMask = 0;
	for (int i = 0; i < (int)significantBits; i++) {
		bitMask = bitMask | (0b1 << i);
	}

	int mul = (2 << 7) / (2 << (significantBits - 1));

	// generate steganography image
	while (imageIndex < inputImg.GetSize()) {
		if (dataIndex == text.GetText().size() && !repeat) break;

		dataIndex = dataIndex % text.GetText().size();

		uint8_t character = (uint8_t)text.GetText()[dataIndex];
		size_t bitSize = sizeof(char) * 8;

		for (int i = (int)bitSize - 1; i >= 0; i -= (int)significantBits) {
			// sigBits = 3
			// i = 8
			//	shift = 
			// i = 5
			// i = 
			if (imageIndex == inputImg.GetSize()) break;

			int bitshift = i - (significantBits - 1);

			/*uint8_t bits = (bitMask << bitshift) & character;
			bits = bits >> bitshift;*/

			uint8_t bits = 0;

			if (bitshift >= 0) {
				bits = (bitMask << bitshift) & character;
				bits = bits >> bitshift;
			}
			else {
				bitshift *= -1;
				bits = (bitMask >> bitshift) & character;
				bits = bits << bitshift;
			}

			uint8_t imageData = inputImg.GetData(imageIndex);
			imageData = (imageData & (~bitMask)) | bits;

			outputImg.SetData(imageIndex, imageData);

			sigBits.SetData(imageIndex, (uint8_t)((255 * (int)bits) / (int)bitMask));

			imageIndex++;
		}

		dataIndex++;
	}
	
	// generate least significant bits image

	outputImg.Write(out.c_str());
	sigBits.Write(significantBitsImg.c_str());
}
