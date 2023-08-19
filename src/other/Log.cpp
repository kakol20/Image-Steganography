#include "Log.h"

#include <iostream>
#include <fstream>
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

	std::string month = std::to_string(tmnow.tm_mon + 1);
	month = month.size() == 1 ? "0" + month : month;

	std::string day = std::to_string(tmnow.tm_mday);
	day = day.size() == 1 ? "0" + day : day;

	std::string hour = std::to_string(tmnow.tm_hour);
	hour = hour.size() == 1 ? "0" + hour : hour;

	std::string min = std::to_string(tmnow.tm_min);
	min = min.size() == 1 ? "0" + min : min;

	std::string sec = std::to_string(tmnow.tm_sec);
	sec = sec.size() == 1 ? "0" + sec : sec;

	std::string line = std::to_string(tmnow.tm_year + 1900) + "/" + month + "/" + day + " "
		+ hour + ":" + min + ":" + sec + " ";

	std::cout << line;
	Log::Console += line;
}

void Log::Save(const bool overwrite) {
	std::fstream consoleLog;
	if (overwrite) {
		consoleLog.open("console.log", std::ios_base::out);
	}
	else {
		// checks if file exists
		consoleLog.open("console.log", std::ios_base::in);

		if (consoleLog.is_open()) {
			// file exist
			consoleLog.close();
			consoleLog.open("console.log", std::ios_base::app);
		}
		else {
			consoleLog.open("console.log", std::ios_base::out);
		}
	}

	consoleLog << Log::Console;

	consoleLog.close();
}
