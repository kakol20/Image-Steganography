#include "Log.h"

#include <iostream>
#include <ctime>

std::string Log::Console = "";

void Log::Write(const std::string input) {
	std::cout << input;
	Log::Console += input;
}

void Log::EndLine() {
	std::cout << '\n';
	Log::Console += "\n";
}

void Log::StartLine() {
	std::time_t now = std::time(0);

	std::tm tmnow{};

	localtime_s(&tmnow, &now);

	std::string line = std::to_string(tmnow.tm_year + 1900) + "/"
		+ std::to_string(tmnow.tm_mon + 1) + "/"
		+ std::to_string(tmnow.tm_mday) + " "
		+ std::to_string(tmnow.tm_hour) + ":" + std::to_string(tmnow.tm_min) + ":" + std::to_string(tmnow.tm_sec) + " ";

	std::cout << line;
	Log::Console += line;
}
