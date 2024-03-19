#include "dictionaryFunc.h";

const std::string SEPARATOR = "-";
const std::string COMMA = ",";
const std::string SPACE = " ";

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
				std::cout << COMMA;
			}
			std::cout << *it_trans;
		}
		std::cout << std::endl;
	}
	else
	{
		bool found = false;
		bool isFirst = true;

		for (const auto& pair : dict)
		{
			if (pair.second.back() == word)
			{
				found = true;

				if (!isFirst)
				{
					std::cout << COMMA << SPACE;
				}
				std::cout << pair.first;

				isFirst = false;
			}
		}

		if (found)
		{
			std::cout << std::endl;
		}

		if (!found)
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
					dictFile << COMMA;
				}
				dictFile << *it;
			}
			dictFile << std::endl;
		}
	}
}

std::string GetWordFromUser()
{
	std::string word;
	std::getline(std::cin, word);
	std::transform(word.begin(), word.end(), word.begin(), [](unsigned char ch)
		{
			return std::tolower(ch);
		}
	);

	return word;
}
