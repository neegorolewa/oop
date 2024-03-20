#pragma once
#include <iostream>
#include <iosfwd>
#include <windows.h>
#include <string>
#include <fstream>
#include <map>
#include <list>
#include <sstream>
#include <conio.h>
#include <algorithm>
#include <cctype>

bool CheckArguments(const int argc);

std::ifstream GetInputFile(const std::string& inputFileName, std::ostream& output);

void TranslateWord(std::istream& input, std::ostream& output, std::string& word, std::map<std::string, std::list<std::string>>& dict, bool& changes);

std::map<std::string, std::list<std::string>> GetDictionary(std::ifstream& file);

void SaveDictionary(std::string fileName, std::map<std::string, std::list<std::string>>& dict);

std::string GetWordFromUser(std::istream& input);