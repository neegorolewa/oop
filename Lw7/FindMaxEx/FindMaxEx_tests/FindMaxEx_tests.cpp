#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../FindMaxEx/FindMax.h"
#include "../FindMaxEx/Sportsman.h"

TEST_CASE("find max value of sportsman")
{
	WHEN("vector is empty")
	{
		std::vector<Sportsman> empty;
		Sportsman max = { "Job", 200, 100 };
		THEN("max not change, function return false")
		{
			REQUIRE(!FindMax(empty, max, CompareHeight));
			REQUIRE(max.name == "Job");
			REQUIRE(max.height == 200);
			REQUIRE(max.weight == 100);
		}
	}

	WHEN("max by height")
	{
		std::vector<Sportsman> sportsman = {
			{"John", 180, 75},
			{"Jane", 175, 68},
			{"Bob", 190, 82}
		};

		Sportsman max;
		THEN("function return true")
		{
			REQUIRE(FindMax(sportsman, max, CompareHeight));
			REQUIRE(max.name == "Bob");
			REQUIRE(max.height == 190);
			REQUIRE(max.weight == 82);
		}
	}

	WHEN("max by weight")
	{
		std::vector<Sportsman> sportsman = {
			{"John", 180, 75},
			{"Jane", 175, 68},
			{"Bob", 190, 82}
		};

		Sportsman max;
		THEN("function return true")
		{
			REQUIRE(FindMax(sportsman, max, CompareWeight));
			REQUIRE(max.name == "Bob");
			REQUIRE(max.height == 190);
			REQUIRE(max.weight == 82);
		}
	}

	WHEN("one el in vector, max by height")
	{
		std::vector<Sportsman> sportsman = {
			{"John", 180, 75}
		};

		Sportsman max;
		THEN("function return true")
		{
			REQUIRE(FindMax(sportsman, max, CompareHeight));
			REQUIRE(max.name == "John");
			REQUIRE(max.height == 180);
			REQUIRE(max.weight == 75);
		}
	}

	WHEN("one el in vector, max by weight")
	{
		std::vector<Sportsman> sportsman = {
			{"John", 180, 75}
		};

		Sportsman max;
		THEN("function return true")
		{
			REQUIRE(FindMax(sportsman, max, CompareWeight));
			REQUIRE(max.name == "John");
			REQUIRE(max.height == 180);
			REQUIRE(max.weight == 75);
		}
	}
}

TEST_CASE("find max by diff type")
{
	WHEN("vector of int")
	{
		auto func = [](const int first, const int second) { return first < second; };
		std::vector<int> digits = { 1, 2, 3, 4, 5 };
		int max;
		THEN("find max digit in vector, func return true")
		{
			REQUIRE(FindMax(digits, max, func));
			REQUIRE(max == 5);
		}
	}

	WHEN("vector of double")
	{
		auto func = [](const double first, const double second) { return first < second; };
		std::vector<double> digits = { 1.0, 2.67, 3.14, 4.5, 105.0 };
		double max;
		THEN("find max digit in vector, func return true")
		{
			REQUIRE(FindMax(digits, max, func));
			REQUIRE(max == 105.0);
		}
	}
}