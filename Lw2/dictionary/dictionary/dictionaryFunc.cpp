#include "dictionaryFunc.h"

const std::string SEPARATOR = ":";
const std::string COMMA = ", ";
const std::string SPACE = " ";

typedef  std::map<std::string, std::list<std::string>> Dictionary;

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

std::ifstream GetInputFile(const std::string& inputFileName, std::ostream& output)
{
	std::ifstream inputFile(inputFileName);
	if (!inputFile.is_open())
	{
		output << "Failed to open '" << inputFileName << "' for reading\n";
		exit(1);
	}
	return inputFile;
}
//выбрать правильный способ передачи парметров словаря
bool FindWordInDictionary(std::string& word, Dictionary dict)
{
	bool found = false;

	auto it = dict.find(word);

	if (it != dict.end())
	{
		found = true;
	}
	else
	{
		for (const auto& pair : dict)
		{
			if (pair.second.back() == word)
			{
				found = true;
			}
		}
	}

	return found;
}

bool WorkIfWordNotFound(std::string word, Dictionary& dict, std::istream& input, std::ostream& output)
{
	bool changes = false;
	std::string translate;
	output << "Неизвестное слово \"" << word << "\". Введите перевод или пустую строку для отказа.\n";
	std::getline(input, translate);

	if (!translate.empty())
	{
		dict[word].push_back(translate);
		output << "Слово \"" << word << "\" сохранено в словаре как \"" << translate << "\".\n";
		changes = true;

	}
	else
	{
		output << "Cлово \"" << word << "\" проигнорировано\n";
	}

	return changes;
}

//разделить функцию (исключить огромное количество параметров) ВЫПОЛНЕНО
void TranslateWord(std::ostream& output, std::string& word, Dictionary& dict, bool& changes)
{
	bool wordInDict = FindWordInDictionary(word, dict);

	if (wordInDict)
	{
		auto it = dict.find(word);
		if (it != dict.end())
		{
			for (auto it_trans = it->second.begin(); it_trans != it->second.end(); ++it_trans) {
				if (it_trans != it->second.begin()) {
					output << COMMA;
				}
				output << *it_trans;
			}
			output << '\n';
		}
		else
		{
			bool isFirst = true;

			for (const auto& pair : dict)
			{
				if (pair.second.back() == word)
				{
					if (!isFirst)
					{
						output << COMMA;
					}
					output << pair.first;

					isFirst = false;
				}
			}
				
			output << '\n';
		}
	}
	else
	{
		changes = WorkIfWordNotFound(word, dict, std::cin, std::cout);
	}
}

//не использовать прямой передачу ifstream (istream)!!! ВЫПОЛНЕНО
Dictionary GetDictionary(std::istream& file)
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
				size_t start = translation.find_first_not_of(' ');
				if (start != std::string::npos)
				{
					translation = translation.substr(start);
				}

				dict[word].push_back(translation);
			}
		}
	}

	return dict;
}

void SaveDictionary(std::string fileName, Dictionary& dict)
{
	std::ofstream dictFile(fileName);

	if (dictFile.is_open())
	{
		for (const auto& pair : dict) {
			dictFile << pair.first << " " << SEPARATOR << " ";
			for (auto it = pair.second.begin(); it != pair.second.end(); ++it) {
				if (it != pair.second.begin()) {
					dictFile << COMMA;
				}
				dictFile << *it;
			}
			dictFile << std::endl;
		}
	}
}

std::string GetWordFromUser(std::istream& input)
{
	std::string word;
	std::getline(input, word);
	//разобраться с unsigned char
	std::transform(word.begin(), word.end(), word.begin(), [](unsigned char ch)
		{
			return std::tolower(ch);
		}
	);

	return word;
}
