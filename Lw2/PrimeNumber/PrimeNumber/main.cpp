#include "PrimeNumberFunc.h"
#include "GetPrimeNumberSet.h"

int main()
{
	std::string line;
	std::cin >> line;
	CheckValidInputStream(line, std::cout);

	int upperBound = std::stoi(line);
	CheckUpperBoundInRange(upperBound, std::cout);

	std::set<int> primesNum = GeneratePrimeNumbersSet(upperBound);
	PrintPrimeNumbersSet(primesNum, std::cout);

	return 0;

}