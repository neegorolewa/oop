#define CATCH_CONFIG_MAIN
#include <cstdlib>
#include "../../../catch.hpp"
#include "../dictionary/dictionaryFunc.h"

//придумать способ разделять символы (+ для хранения нескольких переводов)
SCENARIO("Empty input file give empty dictionary")
{
	std::string dictFileName = "emptyDict.txt";
	std::ofstream output;
	std::ifstream dictFile = GetInputFile(dictFileName, output);

	//длинный тип (изменить на короткий)
	std::map<std::string, std::list<std::string>> dictFromFile;
	std::map<std::string, std::list<std::string>> rightDict = {};

	dictFromFile = GetDictionary(dictFile);
	REQUIRE(dictFromFile == rightDict);
}

SCENARIO("GetDictionary gives true dictionary from file")
{
	std::string dictFileName = "../dictionary/dict.txt";
	std::ostringstream output;
	std::ifstream dictFile = GetInputFile(dictFileName, output);

	std::map<std::string, std::list<std::string>> dictFromFile;
	std::map<std::string, std::list<std::string>> rightDict = {
		{"dog", {"собака"}},
		{"house", {"дом"}},
		{"cat", {"кошка", "кот", "котяра"}}
	};

	dictFromFile = GetDictionary(dictFile);
	REQUIRE(dictFromFile == rightDict);
}

SCENARIO("Getting a word from the user")
{
	std::map<std::string, std::list<std::string>> rightDict = {
		   {"dog", {"собака"}},
		   {"house", {"дом"}},
		   {"cat", {"кошка", "кот", "котяра"}}
	};

	std::istringstream wordLowerCase("dog");
	std::istringstream wordDiffCase("DoG");
	std::string rightWord = "dog";

	//изучить инструкцию тестов в bdd стиле when than given
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
	std::map<std::string, std::list<std::string>> dict = {
			{"dog", {"собака"}},
			{"house", {"дом"}},
			{"кошка", {"cat"}},
			{"кот", {"cat"}},
	};

	WHEN("Translate RU->EN")
	{
		std::istringstream input;
		std::ostringstream output;
		bool changes = false;
		std::string word = "dog";

		TranslateWord(input, output, word, dict, changes);
		CHECK(output.str() == "собака\n");
	}

	WHEN("Translate EN->RU")
	{
		std::istringstream input;
		std::ostringstream output;
		bool changes = false;
		std::string word = "собака";

		TranslateWord(input, output, word, dict, changes);
		CHECK(output.str() == "dog\n");
	}

	WHEN("Translation belongs to two words")
	{
		std::istringstream input;
		std::ostringstream output;
		bool changes = false;
		std::string word = "cat";

		TranslateWord(input, output, word, dict, changes);
		CHECK(output.str() == "кот, кошка\n");
	}
}

SCENARIO("Word translation not found")
{
	std::map<std::string, std::list<std::string>> dict = {
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


		TranslateWord(input, output, word, dict, changes);
		CHECK(output.str() == "Неизвестное слово \"" + word + "\". Введите перевод или пустую строку для отказа.\n" 
			+ "Слово \"" + word + "\" сохранено в словаре как \"" + translate + "\".\n");

		CHECK(changes == true);
	}

	WHEN("User doesn't add a new word to the dictionary")
	{
		bool changes = false;
		std::string word = "tree";
		std::ostringstream output;
		std::istringstream input("");

		TranslateWord(input, output, word, dict, changes);

		CHECK(output.str() == "Неизвестное слово \"" + word + "\". Введите перевод или пустую строку для отказа.\n"
			+ "Cлово \"" + word + "\" проигнорировано\n");
		CHECK(changes == false);
	}

}

SCENARIO("Сhecking dictionary saving")
{
	char tempFileName[L_tmpnam_s];
	tmpnam_s(tempFileName);

	std::map<std::string, std::list<std::string>> dict = {
			{"dog", {"собака"}},
			{"house", {"дом"}},
			{"кошка", {"cat"}},
			{"кот", {"cat"}},
	};

	std::map<std::string, std::list<std::string>> dictNew = {
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
		std::map<std::string, std::list<std::string>> dictFromFile;
		std::istringstream translate("дерево");

		TranslateWord(translate, output, word, dict, changes);
		SaveDictionary(tempFileName, dict);
		std::ifstream dictFile = GetInputFile(tempFileName, output);
		dictFromFile = GetDictionary(dictFile);

		CHECK(dictFromFile == dictNew);
	}
}