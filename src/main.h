// Image Steganography.h : Include file for standard system include files,
// or project specific include files.

#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <fstream>
#include <string>

#include "../ext/json/json.hpp"

#include "image/Image.h"

using json = nlohmann::json;

// TODO: Reference additional headers your program requires here.

float Map(const float val, const float fromMin, const float fromMax, const float toMin, const float toMax);

#endif // !MAIN_H
