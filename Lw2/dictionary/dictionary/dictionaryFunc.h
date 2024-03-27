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

typedef  std::map<std::string, std::list<std::string>> Dictionary;

bool CheckArguments(const int argc);

std::ifstream GetInputFile(const std::string& inputFileName, std::ostream& output);

bool FindWordInDictionary(std::string& word, Dictionary dict);

bool WorkIfWordNotFound(std::string word, Dictionary& dict, std::istream& input, std::ostream& output);

void TranslateWord(std::ostream& output, std::string& word, Dictionary& dict, bool& changes);

Dictionary GetDictionary(std::istream& file);

void SaveDictionary(std::string fileName, Dictionary& dict);

std::string GetWordFromUser(std::istream& input);