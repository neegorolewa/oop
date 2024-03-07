#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../HtmlDecode/HtmlDecode.h"

//Добавить тест амперсанд последнее место

SCENARIO("Decode empty string gives empty string")
{
	REQUIRE(HtmlDecode("").empty());
}

SCENARIO("If string not consist of html-entity then decode gives string itself")
{
	REQUIRE(HtmlDecode("Cat") == "Cat");
}

SCENARIO("If string consist of html-entity, they must be decoded")
{
	REQUIRE(HtmlDecode("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s") == "Cat <says> \"Meow\". M&M's");
}

SCENARIO("If there is an error in the html-entity")
{
	REQUIRE(HtmlDecode("Cat &tl;says&gt; &quot;Meow&quot;. M&amp;M&apos;s") == "Cat &tl;says> \"Meow\". M&M's");
}

SCENARIO("If html-entity in the end")
{
	REQUIRE(HtmlDecode("Cat &amp;") == "Cat &");
}

SCENARIO("If input stream consist of one html-entity")
{
	REQUIRE(HtmlDecode("&amp;") == "&");
}

SCENARIO("DecodeLines")
{
	std::ostringstream output;

	WHEN("Input stream is empty")
	{
		std::istringstream input("");
		THEN("Output stream also is empty")
		{
			HtmlDecodeLines(input, output);
			CHECK(output.str().empty());
			CHECK(input.eof());
		}
	}

	WHEN("Input stream consist of one line")
	{
		std::istringstream input("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s");
		THEN("Output stream is decoded")
		{
			HtmlDecodeLines(input, output);
			CHECK(output.str() == "Cat <says> \"Meow\". M&M's\n");
			CHECK(input.eof());
		}
	}

	WHEN("Input stream consist of several line")
	{
		std::istringstream input("Cat &lt;says&gt;\n&quot;Meow&quot;. M&amp;M&apos;s");
		THEN("Output stream is decoded several lines")
		{
			HtmlDecodeLines(input, output);
			CHECK(output.str() == "Cat <says>\n\"Meow\". M&M's\n");
			CHECK(input.eof());
		}
	}
}
