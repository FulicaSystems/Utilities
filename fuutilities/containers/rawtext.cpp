#include "rawtext.hpp"

Utils::RawText::RawText(const std::string& str)
	: raw(str)
{
	length = (int)str.length();
}

void Utils::RawText::setCursor(const int pos)
{
	cursor = pos;
}

bool Utils::RawText::getline(std::string& out)
{
	if (cursor >= length)
		return false;

	out = "";
	while (!(raw[cursor] == '\n' || raw[cursor] == '\0'))
		out += raw[cursor++];

	++cursor;
	return true;
}

std::string& Utils::RawText::getRawText()
{
	return raw;
}