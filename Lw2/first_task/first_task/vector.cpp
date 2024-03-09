#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include "WorkWithVector.h"

int main(int argc, char* argv[])
{
	std::vector<double> numbers(std::istream_iterator<double>(std::cin), (std::istream_iterator<double>()));

	if (std::cin.bad() || !std::cin.eof())
	{
		std::cout << "Fail to read file or numbers";
		return 1;
	}

	DivArrayOnHalfOfMax(numbers);

	std::sort(numbers.begin(), numbers.end());

	//printVector
	PrintSortVector(numbers);

	return 0;
}