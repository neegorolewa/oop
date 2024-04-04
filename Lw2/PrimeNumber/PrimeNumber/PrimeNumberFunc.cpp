#include "PrimeNumberFunc.h"

const int MIN_INPUT = 1;
const int MAX_INPUT = 100000000;
const char SEPARATOR = ' ';

void CheckValidInputStream(const std::string& line, std::ostream& output)
{
	for (char ch : line)
	{
		if (!std::isdigit(ch))
		{
			output << "Invalid data, enter number\n";
			exit(1);
		}
	}
}

void CheckUpperBoundInRange(int upperBound, std::ostream& output)
{
	if (upperBound < MIN_INPUT || upperBound > MAX_INPUT)
	{
		output << "Invalid number, number should be in range [1..1000000]\n";
		exit(1);
	}
	
}

void PrintPrimeNumbersSet(const std::set<int>& primesNumber, std::ostream& output)
{
	for (int number : primesNumber)
	{
		output << number << SEPARATOR;
	}
	output << '\n';
}