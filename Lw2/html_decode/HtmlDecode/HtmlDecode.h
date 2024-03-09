#pragma once
#include <string>
#include <iosfwd>

std::string HtmlDecode(const std::string& html);

void HtmlDecodeLines(std::istream& input, std::ostream& output);

void CheckEntity(int& pos, std::string& decodedLine, const std::string& subject);