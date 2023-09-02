#include "Txt.h"

#include <fstream>

#include "Log.h"

bool Txt::Read(const char* file) {

	Log::StartLine();

	std::ifstream input(file);

	if (!input.is_open()) {
		Log::Write("Read failed ");
		Log::Write(file);
		Log::EndLine();

		return false;
	}
	else {
		Log::Write("Read success ");
		Log::Write(file);
		Log::EndLine();
	}

	m_text = "";

	m_text.assign(
		(std::istreambuf_iterator<char>(input)),
		(std::istreambuf_iterator<char>())
	);

	Log::StartLine();
	Log::Write("Text: ");
	Log::EndLine();
	Log::Write(m_text);
	Log::EndLine();

	return true;
}