#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../MyString/CMyString.h"

TEST_CASE("Check creating MyString")
{
	WHEN("Create without args")
	{
		CMyString str;
		THEN("len = 0, str - empty")
		{
			REQUIRE(str.GetLength() == 0);
			REQUIRE(std::string(str.GetStringData()).empty());
		}
	}

	WHEN("Create char* string")
	{
		const char* str = "Text";
		CMyString mystr(str);
		THEN("len = text length, str has end symbol")
		{
			REQUIRE(strcmp(mystr.GetStringData(), str) == 0);
			REQUIRE(mystr.GetLength() == strlen(str));
		}
	}

	WHEN("Creating char* str contains nulling string code")
	{
		const char* str = "Some \0 text";
		CMyString myStr(str);
		THEN("Str will has end symbol and length == text.length")
		{
			CHECK(strcmp(myStr.GetStringData(), str) == 0);
			CHECK(myStr.GetLength() == strlen(str));
		}
	}

	WHEN("Create with char* str with length")
	{
		const char* str = "Some text";
		CMyString myStr(str, strlen(str));
		THEN("Str will has end symbol and length == text.length")
		{
			CHECK(strcmp(myStr.GetStringData(), str) == 0);
			CHECK(myStr.GetLength() == strlen(str));
		}
	}

	WHEN("Copy constructor")
	{
		const char* str = "Text";
		CMyString str1(str);
		CMyString str2(str1);
		THEN("str1 == str2")
		{
			REQUIRE(str1.GetLength() == str2.GetLength());
			REQUIRE(strcmp(str1.GetStringData(), str2.GetStringData()) == 0);
		}
	}

	WHEN("Move constructor")
	{
		const char* str = "Text";
		CMyString str1(str);
		CMyString str2(std::move(str1));
		THEN("text str1 == str2, str1 is empty")
		{
			REQUIRE(str1.GetLength() == 0);
			REQUIRE(strcmp(str1.GetStringData(), "") == 0);
			REQUIRE(strcmp(str2.GetStringData(), "Text") == 0);
		}
	}

	WHEN("STL string")
	{
		std::string str = "text";
		CMyString str1(str);
		THEN("str1 == str")
		{
			REQUIRE(str1.GetLength() == str.size());
			REQUIRE((strcmp(str1.GetStringData(), str.c_str()) == 0));
		}
	}

	WHEN("STL string with nullin code")
	{
		std::string str = "text\0 check";
		CMyString str1(str);
		THEN("str == str1")
		{
			REQUIRE(str.size() == str1.GetLength());
			REQUIRE(strcmp(str1.GetStringData(), str.c_str()) == 0);
		}
	}
}

TEST_CASE("Check substring method")
{
	WHEN("true substring")
	{
		const char* str = "test text";
		CMyString str1(str);
		CMyString sub = str1.SubString(1, 5);
		THEN("sub is correct")
		{
			REQUIRE(strcmp(sub.GetStringData(), "est t") == 0);
		}
	}

	WHEN("start > len str")
	{
		const char* str = "test text";
		CMyString str1(str);
		THEN("throw exception")
		{
			REQUIRE_THROWS_WITH(str1.SubString(12, 3), "Start symbol is out of range");
		}
	}

	WHEN("start < 0")
	{
		const char* str = "test text";
		CMyString str1(str);
		THEN("throw exception")
		{
			REQUIRE_THROWS_WITH(str1.SubString(-12, 3), "Start symbol is out of range");
		}
	}

	WHEN("str after len substr > base len")
	{
		const char* str = "test text";
		CMyString str1(str);
		CMyString sub = str1.SubString(5, 14);
		THEN("get all symbol after start")
		{
			REQUIRE(strcmp(sub.GetStringData(), "text") == 0);
		}
	}

	WHEN("Count to get is negative")
	{
		const char* str = "test text";
		CMyString myStr(str);
		CMyString substr = myStr.SubString(5, -5);
		THEN("Sub string will contain symbols after start")
		{
			REQUIRE(strcmp(substr.GetStringData(), "text") == 0);
		}
	}
}

TEST_CASE("Check Clear() method")
{
	WHEN("string is empty")
	{
		CMyString str;
		str.Clear();
		THEN("str is empty")
		{
			REQUIRE(str.GetLength() == 0);
			REQUIRE(strcmp(str.GetStringData(), "") == 0);
		}
	}

	WHEN("string is not empty")
	{
		const char* str0 = "test text";
		CMyString str(str0);
		str.Clear();
		THEN("str is empty")
		{
			REQUIRE(str.GetLength() == 0);
			REQUIRE(strcmp(str.GetStringData(), "") == 0);
		}
	}
}

TEST_CASE("operator =")
{
	WHEN("string copy another string")
	{
		const char* str = "test text";
		CMyString str1;
		CMyString str2(str);
		str1 = str2;
		THEN("str1, str2 == str")
		{
			REQUIRE(strcmp(str1.GetStringData(), str) == 0);
			REQUIRE(strcmp(str2.GetStringData(), str) == 0);
		}
	}

	WHEN("myself copy")
	{
		CMyString str("text");
		str = str;
		THEN("not changes")
		{
			REQUIRE(strcmp(str.GetStringData(), "text") == 0);
		}
	}

	WHEN("use move with =")
	{
		std::string text = "text";
		CMyString str;
		CMyString str1(text);
		str = std::move(str1);
		THEN("str == text", str1 is empty)
		{
			REQUIRE(strcmp(str.GetStringData(), text.c_str()) == 0);
			REQUIRE(strcmp(str1.GetStringData(), "") == 0);
			REQUIRE(str1.GetLength() == 0);
		}
	}

	WHEN("move myself")
	{
		CMyString str("text");
		str = std::move(str);
		THEN("not changes")
		{
			REQUIRE(strcmp(str.GetStringData(), "text") == 0);
		}
	}
}

TEST_CASE("operator +")
{
	WHEN("mystr + mystr")
	{
		CMyString str1("test ");
		CMyString str2("text");
		CMyString res = str1 + str2;
		THEN("res = concatenation str1 and str2")
		{
			REQUIRE(strcmp(res.GetStringData(), "test text") == 0);
		}
	}

	WHEN("string + mystr")
	{
		CMyString str1("test ");
		std::string str2 = "text";
		CMyString res = str1 + str2;
		THEN("res = concatenation str1 and str2")
		{
			REQUIRE(strcmp(res.GetStringData(), "test text") == 0);
		}
	}

	WHEN("char* + mystr")
	{
		CMyString str1("test ");
		const char* str2 = "text";
		CMyString res = str1 + str2;
		THEN("res = concatenation str1 and str2")
		{
			REQUIRE(strcmp(res.GetStringData(), "test text") == 0);
		}
	}
}

TEST_CASE("operator +=")
{
	WHEN("success +=")
	{
		CMyString str1("test ");
		CMyString str2("text");
		str1 += str2;
		THEN("str1 = str1 + str2")
		{
			REQUIRE(strcmp(str1.GetStringData(), "test text") == 0);
		}
	}

	WHEN("empty += mystr")
	{
		CMyString str1;
		CMyString str2("text");
		str1 += str2;
		THEN("str1 = str2")
		{
			REQUIRE(strcmp(str1.GetStringData(), "text") == 0);
		}
	}

	WHEN("some +=")
	{
		CMyString str1("1");
		CMyString str2("2");
		CMyString str3("3");
		(str1 += str2) += str3;
		THEN("str1 = str1 + str2 + str3")
		{
			REQUIRE(strcmp(str1.GetStringData(), "123") == 0);
		}
	}

	WHEN("len < newLen")
	{
		CMyString str1("1");
		CMyString str2("2345");
		(str1 += str2);
		THEN("str1 = str1 + str2")
		{
			REQUIRE(strcmp(str1.GetStringData(), "12345") == 0);
		}
	}
}

TEST_CASE("operator ==")
{
	WHEN("the same text")
	{
		CMyString str1("text");
		CMyString str2("text");
		THEN("it's true")
		{
			REQUIRE(str1 == str2);
		}
	}

	WHEN("the diff text")
	{
		CMyString str1("text");
		CMyString str2("TEXT");
		THEN("it's false")
		{
			REQUIRE(!(str1 == str2));
		}
	}
}

TEST_CASE("operator !=")
{
	WHEN("the same text")
	{
		CMyString str1("text");
		CMyString str2("text");
		THEN("it's true")
		{
			REQUIRE(!(str1 != str2));
		}
	}

	WHEN("the diff text")
	{
		CMyString str1("text");
		CMyString str2("TEXT");
		THEN("it's false")
		{
			REQUIRE(str1 != str2);
		}
	}
}

TEST_CASE("operator <")
{
	WHEN("str1 < str2")
	{
		CMyString str1("123");
		CMyString str2("456");
		THEN("it's true")
		{
			REQUIRE(str1 < str2);
		}
	}

	WHEN("str1 > str2")
	{
		CMyString str1("456");
		CMyString str2("123");
		THEN("it's false")
		{
			REQUIRE(!(str1 < str2));
		}
	}

	WHEN("str1 = str2")
	{
		CMyString str1("123");
		CMyString str2("123");
		THEN("it's false")
		{
			REQUIRE(!(str1 < str2));
		}
	}
}

TEST_CASE("operator >")
{
	WHEN("str1 > str2")
	{
		CMyString str1("456");
		CMyString str2("123");
		THEN("it's true")
		{
			REQUIRE(str1 > str2);
		}
	}

	WHEN("str1 < str2")
	{
		CMyString str1("123");
		CMyString str2("456");
		THEN("it's false")
		{
			REQUIRE(!(str1 > str2));
		}
	}

	WHEN("str1 = str2")
	{
		CMyString str1("123");
		CMyString str2("123");
		THEN("it's false")
		{
			REQUIRE(!(str1 > str2));
		}
	}
}

TEST_CASE("operator <=")
{
	WHEN("str1 <= str2")
	{
		CMyString str1("123");
		CMyString str2("456");
		THEN("it's true")
		{
			REQUIRE(str1 <= str2);
		}
	}

	WHEN("str1 > str2")
	{
		CMyString str1("456");
		CMyString str2("123");
		THEN("it's false")
		{
			REQUIRE(!(str1 <= str2));
		}
	}

	WHEN("str1 = str2")
	{
		CMyString str1("123");
		CMyString str2("123");
		THEN("it's true")
		{
			REQUIRE(str1 <= str2);
		}
	}
}

TEST_CASE("operator >=")
{
	WHEN("str1 > str2")
	{
		CMyString str1("456");
		CMyString str2("123");
		THEN("it's true")
		{
			REQUIRE(str1 >= str2);
		}
	}

	WHEN("str1 < str2")
	{
		CMyString str1("123");
		CMyString str2("456");
		THEN("it's false")
		{
			REQUIRE(!(str1 >= str2));
		}
	}

	WHEN("str1 = str2")
	{
		CMyString str1("123");
		CMyString str2("123");
		THEN("it's true")
		{
			REQUIRE(str1 >= str2);
		}
	}
}

TEST_CASE("operator []")
{
	WHEN("Read")
	{
		CMyString str("test text");
		THEN("right char in index")
		{
			CHECK(str[3] == 't');
		}
	}

	WHEN("Index not in range")
	{
		CMyString str("test text");
		THEN("throw exception")
		{
			REQUIRE_THROWS_WITH(str[40], "Index out of range");
			REQUIRE_THROWS_WITH(str[-40], "Index out of range");
		}
	}

	WHEN("Set")
	{
		CMyString str("text");
		str[0] = 'T';
		THEN("setting new char")
		{
			REQUIRE(strcmp(str.GetStringData(), "Text") == 0);
		}
	}

	WHEN("Set and index out of range")
	{
		CMyString str("text");
		THEN("setting new char")
		{
			REQUIRE_THROWS_WITH(str[40] == '1', "Index out of range");
			REQUIRE_THROWS_WITH(str[-40] == '1', "Index out of range");
		}
	}
}

TEST_CASE("operator >>")
{
	WHEN("read before space")
	{
		std::istringstream in("test text");
		CMyString str;
		in >> str;
		THEN("str read input before first space")
		{
			REQUIRE(strcmp(str.GetStringData(), "test") == 0);
		}
	}

	WHEN("read befor \n")
	{
		std::istringstream in("test\ntext");
		CMyString str;
		in >> str;
		THEN("str read input before first enter")
		{
			REQUIRE(strcmp(str.GetStringData(), "test") == 0);
		}
	}

	WHEN("read befor eof")
	{
		std::istringstream in("test");
		CMyString str;
		in >> str;
		THEN("str read input before eof")
		{
			REQUIRE(strcmp(str.GetStringData(), "test") == 0);
		}
	}
}

TEST_CASE("operator <<")
{
	WHEN("right writing")
	{
		std::ostringstream out;
		CMyString str("text");
		out << str;
		THEN("out contains str")
		{
			REQUIRE(out.str() == "text");
		}
	}

	WHEN("str has null symbol")
	{
		std::ostringstream out;
		CMyString str("text\0text");
		out << str;
		THEN("out contains str")
		{
			REQUIRE(out.str() == str.GetStringData());
		}
	}
}