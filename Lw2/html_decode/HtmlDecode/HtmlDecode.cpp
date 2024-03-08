#include <iostream>
#include <string>
#include "HtmlDecode.h"

const std::string AMPERSANT_ENTITY = "&amp;";
const std::string QUOTE_ENTITY = "&quot;";
const std::string APOSTROPHE_ENTITY = "&apos;";
const std::string LESS_ENTITY = "&lt;";
const std::string MORE_ENTITY = "&gt;";

const char AMPERSANT_SIGN = '&';
const char QUOTE_SIGN = '\"';
const char APOSTROPHE_SIGN = '\'';
const char LESS_SIGN = '<';
const char MORE_SIGN = '>';

const int AMPERSANT_SIZE = 5;
const int QUOTE_SIZE = 6;
const int APOSTROPHE_SIZE = 6;
const int LESS_SIZE = 4;
const int MORE_SIZE = 4;

std::string HtmlDecode(const std::string& subject)
{
	std::string decodedLine;
	int pos = 0;
	while (pos < subject.size())
	{

		if (subject[pos] != AMPERSANT_SIGN)
		{
			decodedLine += subject[pos];
			pos++;
		}
		else
		{
			if (subject.substr(pos, QUOTE_SIZE) == QUOTE_ENTITY)
			{
				decodedLine += QUOTE_SIGN;
				pos += 6;
			}
			else if (subject.substr(pos, APOSTROPHE_SIZE) == APOSTROPHE_ENTITY)
			{
				decodedLine += APOSTROPHE_SIGN;
				pos += 6;
			}
			else if (subject.substr(pos, LESS_SIZE) == LESS_ENTITY)
			{
				decodedLine += LESS_SIGN;
				pos += 4;
			}
			else if (subject.substr(pos, MORE_SIZE) == MORE_ENTITY)
			{
				decodedLine += MORE_SIGN;
				pos += 4;
			}
			else if (subject.substr(pos, AMPERSANT_SIZE) == AMPERSANT_ENTITY)
			{
				decodedLine += AMPERSANT_SIGN;
				pos += 5;
			}
			else
			{
				decodedLine += subject[pos];
				pos++;
			}
		}
	}

	return decodedLine;
}

void HtmlDecodeLines(std::istream& input, std::ostream& output)
{
	std::string line;
	while (std::getline(input, line))
	{
		output << HtmlDecode(line) << '\n';
	}
}
