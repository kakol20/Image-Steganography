#pragma once
#include <string>

/// <summary>
/// Reads an entire txt file and stores in std::string variable
/// </summary>
class Txt {
public:
	Txt() {};
	~Txt() {};

	bool Read(const char* file);

	std::string GetText() const { return m_text; };

private:
	std::string m_text;
};