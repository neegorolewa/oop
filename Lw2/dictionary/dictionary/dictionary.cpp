#include "dictionaryFunc.h";

const std::string END_PROGRAM = "...";

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	if (!CheckArguments(argc))
	{
		return 1;
	}

	std::ifstream inputFile = GetInputFile(argv[1], std::cout);

	std::map<std::string, std::list<std::string>> dictionary;

	dictionary = GetDictionary(inputFile);

	bool changes = false;

	while (true)
	{
		std::string word = GetWordFromUser(std::cin);

		if (word == END_PROGRAM)
		{
			if (changes == true)
			{
				std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n";
				std::string request;
				std::getline(std::cin, request);

				if (request == "Y" || request == "y")
				{
					SaveDictionary(argv[1], dictionary);
				}

			}

			break;
		};

		TranslateWord(std::cout, word, dictionary, changes);
	}

	return 0;
}

