#pragma once
#include <string>
#include <iosfwd>

//const std::string DOUBLE_QUOTE = "&quot;";
//const std::string APOSTROPHE = "&apos;";
//const std::string SIGN_LESS = "&lt;";
//const std::string SIGN_MORE = "&gt;";
//const std::string AMPERSAND = "&amp;";
//
//const char AMPERSAND = '&';
//
//const char DECODE_DOUBLE_QUOTE = '"';
//const char DECODE_APOSTROPHE = '\'';
//const char DECODE_SIGN_LESS = '<';
//const char DECODE_SIGN_MORE = '>';
//const char DECODE_AMPERSAND ='&';
//
//const int LEN_DOUBLE_QUOTE = 5;
//const int LEN_APOSTROPHE = 5;
//const int LEN_SIGN_LESS = 3;
//const int LEN_SIGN_MORE = 3;
//const int LEN_AMPERSAND = 4;

std::string HtmlDecode(const std::string& html);

void HtmlDecodeLines(std::istream& input, std::ostream& output);