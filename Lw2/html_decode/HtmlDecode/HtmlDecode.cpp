#include <iostream>
#include "HtmlDecode.h"

std::string HtmlDecode(const std::string& subject)
{
	std::string decodedLine;
	int pos = 0;
	while (pos < subject.size())
	{

		if (subject[pos] == '&')
		{
			if (subject.substr(pos, 6) == "&quot;")
			{
				decodedLine += '\"';
				pos += 6;
			}
			else if (subject.substr(pos, 6) == "&apos;")
			{
				decodedLine += '\'';
				pos += 6;
			}
			else if (subject.substr(pos, 4) == "&lt;")
			{
				decodedLine += '<';
				pos += 4;
			}
			else if (subject.substr(pos, 4) == "&gt;")
			{
				decodedLine += '>';
				pos += 4;
			}
			else if (subject.substr(pos, 5) == "&amp;")
			{
				decodedLine += '&';
				pos += 5;
			}
			//дублирование
			else
			{
				decodedLine += subject[pos];
				pos++;
			}
		}
		else
		{
			decodedLine += subject[pos];
			pos++;
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
