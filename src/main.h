// Image Steganography.h : Include file for standard system include files,
// or project specific include files.

#ifndef MAIN_H
#define MAIN_H

//#define USE_MAP

#include <iostream>
#include <fstream>
#include <string>

#include "../ext/json/json.hpp"

#include "image/Image.h"
#include "image/Dither.h"

#include "process/Img2Img.h"
#include "process/Text2Img.h"

#include "other/Log.h"

using json = nlohmann::json;

// TODO: Reference additional headers your program requires here.

#ifdef USE_MAP
float Map(const float val, const float fromMin, const float fromMax, const float toMin, const float toMax);
#endif // USE_MAP


#endif // !MAIN_H
