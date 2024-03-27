#include "dictionaryFunc.h";

const std::string SEPARATOR = "-";
const std::string COMMA = ", ";
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

//разделить функцию (исключить огромное количество параметров)
//какие проблемы с выходными аргументами
void TranslateWord(std::istream& input, std::ostream& output, std::string& word, std::map<std::string, std::list<std::string>>& dict, bool& changes)
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
		output << std::endl;
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
					output << COMMA;
				}
				output << pair.first;

				isFirst = false;
			}
		}

		if (found)
		{
			output << '\n';
		}

		if (!found)
		{
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
		}
	}
}

//не использовать прямой передачу ifstream (istream)!!!
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
				size_t start = translation.find_first_not_of(' ');
				if (start != std::string::npos) {
					translation = translation.substr(start);
				}

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

std::string GetWordFromUser(std::istream& input)
{
	std::string word;
	std::getline(input, word);
	std::transform(word.begin(), word.end(), word.begin(), [](unsigned char ch)
		{
			return std::tolower(ch);
		}
	);

	return word;
}
