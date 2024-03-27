#define CATCH_CONFIG_MAIN
#include <cstdlib>
#include "../../../catch.hpp"
#include "../dictionary/dictionaryFunc.h"

typedef  std::map<std::string, std::list<std::string>> Dictionary;

//придумать способ разделять символы (+ для хранения нескольких переводов) (ВЫПОЛНЕНО)
SCENARIO("Empty input file give empty dictionary")
{
	std::string dictFileName = "emptyDict.txt";
	std::ofstream output;
	std::ifstream dictFile = GetInputFile(dictFileName, output);

	//длинный тип (изменить на короткий) (ВЫПОЛНЕНО)
	Dictionary dictFromFile;
	Dictionary rightDict = {};

	dictFromFile = GetDictionary(dictFile);
	REQUIRE(dictFromFile == rightDict);
}

SCENARIO("GetDictionary gives true dictionary from file")
{
	std::string dictFileName = "../dictionary/dict.txt";
	std::ostringstream output;
	std::ifstream dictFile = GetInputFile(dictFileName, output);

	Dictionary dictFromFile;
	Dictionary rightDict = {
		{"dog", {"собака"}},
		{"house", {"дом"}},
	};

	dictFromFile = GetDictionary(dictFile);
	REQUIRE(dictFromFile == rightDict);
}

SCENARIO("Getting a word from the user")
{
	Dictionary rightDict = {
		   {"dog", {"собака"}},
		   {"house", {"дом"}},
	};

	std::istringstream wordLowerCase("dog");
	std::istringstream wordDiffCase("DoG");
	std::string rightWord = "dog";

	//изучить инструкцию тестов в bdd стиле when than given (ВЫПОЛНЕНО)
	WHEN("Word in lower case")
	{
		std::string word = GetWordFromUser(wordLowerCase);
		CHECK(word == rightWord);
	}

	WHEN("Word in different case")
	{
		std::string word = GetWordFromUser(wordDiffCase);
		CHECK(word == rightWord);
	}
}

SCENARIO("User's word has a translation, translation should be in console")
{
	Dictionary dict = {
			{"dog", {"собака"}},
			{"house", {"дом"}},
			{"кошка", {"cat"}},
			{"кот", {"cat"}},
	};

	WHEN("Translate RU->EN")
	{
		std::ostringstream output;
		bool changes = false;
		std::string word = "dog";

		THEN("Translate will be done")
		{
			TranslateWord(output, word, dict, changes);
			CHECK(output.str() == "собака\n");
		}
	}

	WHEN("Translate EN->RU")
	{
		std::ostringstream output;
		bool changes = false;
		std::string word = "собака";

		THEN("Translate will be done")
		{
			TranslateWord(output, word, dict, changes);
			CHECK(output.str() == "dog\n");
		}
	}

	WHEN("Translation belongs to two words")
	{
		std::istringstream input;
		std::ostringstream output;
		bool changes = false;
		std::string word = "cat";

		THEN("Translate will be done")
		{
			TranslateWord(output, word, dict, changes);
			CHECK(output.str() == "кот, кошка\n");
		}
	}
}

SCENARIO("Word translation not found")
{
	Dictionary dict = {
			{"dog", {"собака"}},
			{"house", {"дом"}},
			{"кошка", {"cat"}},
			{"кот", {"cat"}},
	};

	WHEN("User adds a new word to the dictionary")
	{
		bool changes = false;
		std::string word = "tree";
		std::string translate = "дерево";
		std::ostringstream output;
		std::istringstream input("дерево");

		THEN("Will be output text about not found word and text about right save")
		{
			changes = WorkIfWordNotFound(word, dict, input, output);
			CHECK(output.str() == "Неизвестное слово \"" + word + "\". Введите перевод или пустую строку для отказа.\n"
				+ "Слово \"" + word + "\" сохранено в словаре как \"" + translate + "\".\n");

			CHECK(changes == true);
		}
	}

	WHEN("User doesn't add a new word to the dictionary")
	{
		bool changes = false;
		std::string word = "tree";
		std::ostringstream output;
		std::istringstream input("");

		THEN("Will be output text about not found word and text about ignore new word")

		{
			changes = WorkIfWordNotFound(word, dict, input, output);

			CHECK(output.str() == "Неизвестное слово \"" + word + "\". Введите перевод или пустую строку для отказа.\n"
				+ "Cлово \"" + word + "\" проигнорировано\n");
			CHECK(changes == false);
		}
	}

}

SCENARIO("Сhecking dictionary saving")
{
	char tempFileName[L_tmpnam_s];
	tmpnam_s(tempFileName);

	Dictionary dict = {
			{"dog", {"собака"}},
			{"house", {"дом"}},
			{"кошка", {"cat"}},
			{"кот", {"cat"}},
	};

	Dictionary dictNew = {
			{"dog", {"собака"}},
			{"house", {"дом"}},
			{"кошка", {"cat"}},
			{"кот", {"cat"}},
			{"tree", {"дерево"}},
	};

	std::ofstream output(tempFileName);
	bool changes = false;
	std::string word = "tree";
	
	WHEN("User save changes")
	{
		Dictionary dictFromFile;
		std::istringstream translate("дерево");

		THEN("Dictionary will be right saving")
		{
			WorkIfWordNotFound(word, dict, translate, output);
			SaveDictionary(tempFileName, dict);
			std::ifstream dictFile = GetInputFile(tempFileName, output);
			dictFromFile = GetDictionary(dictFile);

			CHECK(dictFromFile == dictNew);
		}
	}
}