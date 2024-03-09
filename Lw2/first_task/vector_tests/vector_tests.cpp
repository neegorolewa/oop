#include <iostream>
#include <vector>
#include <string>
#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../first_task/WorkWithVector.h"

SCENARIO("If input stream is empty")
{
	std::vector<double> empty;
	DivArrayOnHalfOfMax(empty);
	REQUIRE(empty.empty());
}

SCENARIO("Delete vector on max element with value 2 gives same vector")
{
	std::vector<double> vector{ 2, 2, 2, 2 };
	std::vector<double> sameVector{ 2, 2, 2, 2 };
	DivArrayOnHalfOfMax(vector);
	REQUIRE(vector == sameVector);
}

SCENARIO("Del vector contains negative values with max element with value 1 gives vector multipy 2 ")
{
	std::vector<double> vector{ -1.2, -10.23, -1234, 1 };
	std::vector<double> zeroVector{ -2.4, -20.46, -2468, 2 };
	DivArrayOnHalfOfMax(vector);
	REQUIRE(vector == zeroVector);
}

SCENARIO("Del vector contains negative values with max element with value -2 gives vector non-negative values ")
{
	std::vector<double> vector{ -1.2, -10.23, -1234, -1 };
	std::vector<double> zeroVector{ 2.4, 20.46, 2468, 2 };
	DivArrayOnHalfOfMax(vector);
	REQUIRE(vector == zeroVector);
}

SCENARIO("If input stream contains non-double values")
{
	std::istringstream iss("1 1 a");
	std::vector<double> numbers(std::istream_iterator<double>(iss), (std::istream_iterator<double>()));
	std::string coutMessage;
	if (iss.bad() || !iss.eof())
	{
		coutMessage = "Failed to read data from input stream";
	}
	REQUIRE(coutMessage == "Failed to read data from input stream");
}