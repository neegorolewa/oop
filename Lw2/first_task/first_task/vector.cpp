#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include "Add.h"

int main(int argc, char* argv[])
{
	if (argc != 1)
	{
		std::cout << "Invalid arguments count\n";
		return 1;
	}

	std::vector<double> numbers(std::istream_iterator<double>(std::cin), (std::istream_iterator<double>()));

	if (std::cin.bad() || !std::cin.eof())
	{
		std::cout << "Fail to read file or numbers";
		return 1;
	}

	DivArrayOnHalfOfMax(numbers);

	std::sort(numbers.begin(), numbers.end());

	std::cout << std::setprecision(2) << std::fixed;
	std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<double>(std::cout, " "));
	
	return 0;
}