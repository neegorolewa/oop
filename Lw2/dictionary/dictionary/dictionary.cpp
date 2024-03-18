#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <map>
#include <list>
#include <sstream>
#include <conio.h>

const std::string SEPARATOR = "-";

struct Args
{
	std::string inputFileName;
};

bool CheckArguments(const int argc)
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: dictionary.exe <dictionary file name>\n";
		return false;
	}
	return true;
}

std::ifstream GetInputFile(const std::string& inputFileName)
{
	std::ifstream inputFile(inputFileName);
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open '" << inputFileName << "' for reading\n";
		exit(1);
	}
	return inputFile;
}

void TranslateWord(std::string& word, std::map<std::string, std::list<std::string>>& dict, bool& changes)
{
	auto it = dict.find(word);
	if (it != dict.end())
	{
		for (auto it_trans = it->second.begin(); it_trans != it->second.end(); ++it_trans) {
			if (it_trans != it->second.begin()) {
				std::cout << ",";
			}
			std::cout << *it_trans;
		}
		std::cout << std::endl;
	}
	else
	{
		std::string translate;
		std::cout << "Неизвестное слово \"" << word << "\". Введите перевод или пустую строку для отказа.\n";
		std::getline(std::cin, translate);

		if (!translate.empty())
		{
			dict[word].push_back(translate);
			std::cout << "Слово \"" << word << "\" сохранено в словаре как \"" << translate << "\".\n";
			changes = true;

		}
		else
		{
			std::cout << "Cлово \"" << word << "\" проигнорировано\n";
		}
	}
}

std::map<std::string, std::list<std::string>> GetDictionary(std::ifstream& file)
{
	std::map<std::string, std::list<std::string>> dict;
	std::string line;
	while (std::getline(file, line))
	{
		size_t pos = line.find(SEPARATOR);
		if (pos != std::string::npos)
		{
			std::string word = line.substr(0, pos - 1);
			std::string translations = line.substr(pos + 2);

			std::istringstream iss(translations);
			std::string translation;
			while (std::getline(iss, translation, ','))
			{
				dict[word].push_back(translation);
			}
		}
	}

	return dict;
}

void SaveDictionary(std::string fileName, std::map<std::string, std::list<std::string>>& dict)
{
	std::ofstream dictFile(fileName);

	if (dictFile.is_open())
	{
		for (const auto& pair : dict) {
			dictFile << pair.first << " " << SEPARATOR << " ";
			for (auto it = pair.second.begin(); it != pair.second.end(); ++it) {
				if (it != pair.second.begin()) {
					dictFile << ",";
				}
				dictFile << *it;
			}
			dictFile << std::endl;
		}
	}
}

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	if (!CheckArguments(argc))
	{
		return 1;
	}

	std::ifstream inputFile = GetInputFile(argv[1]);

	std::map<std::string, std::list<std::string>> dictionary;

	dictionary = GetDictionary(inputFile);

	bool changes = false;

	while (true)
	{
		std::string word;
		std::getline(std::cin, word);

		if (word == "...")
		{
			if (changes == true)
			{
				std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n";
				std::string request;
				std::getline(std::cin, request);

				if (request == "Y" || "y")
				{
					SaveDictionary(argv[1], dictionary);
				}

			}

			break;
		};

		TranslateWord(word, dictionary, changes);
	}

	return 0;
}

