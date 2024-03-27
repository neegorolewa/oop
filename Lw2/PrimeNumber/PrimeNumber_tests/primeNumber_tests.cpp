#define CATCH_CONFIG_MAIN
#include <sstream>
#include "debug_macros.h"
#include "../../../catch.hpp"
#include"../PrimeNumber/GetPrimeNumberSet.h"
#include "../PrimeNumber/PrimeNumberFunc.h"

SCENARIO("Test 1")
{
	int upperBound = 9;
	std::set<int> trueSet = { 2, 3, 5, 7 };
	std::set<int> primesSet = GeneratePrimeNumbersSet(upperBound);
	REQUIRE(primesSet == trueSet);
}

SCENARIO("Test 2")
{
	int upperBound = 20;
	std::set<int> trueSet = { 2, 3, 5, 7, 11, 13, 17, 19 };
	std::set<int> primesSet = GeneratePrimeNumbersSet(upperBound);
	REQUIRE(primesSet == trueSet);
}

SCENARIO("Test 3")
{
	int upperBound = 1;
	std::set<int> trueSet = {};
	std::set<int> primesSet = GeneratePrimeNumbersSet(upperBound);
	REQUIRE(primesSet == trueSet);
}

SCENARIO("Test 4")
{
	int upperBound = 2;
	std::set<int> trueSet = { 2 };
	std::set<int> primesSet = GeneratePrimeNumbersSet(upperBound);
	REQUIRE(primesSet == trueSet);
}

SCENARIO("Check min upperBound")
{
	int upperBound = 0;
	std::set<int> trueSet = {};
	std::set<int> primesSet = GeneratePrimeNumbersSet(upperBound);
	REQUIRE(primesSet == trueSet);
}

SCENARIO("Check max upperBound and size set with primes number")
{
	int upperBound = 100'000'000;
	int countPrimesNum = 5761455;

	DEBUG_IN_RELEASE
	(
		std::set<int> primesSet = GeneratePrimeNumbersSet(upperBound);
		REQUIRE(countPrimesNum == primesSet.size());
	)
}
