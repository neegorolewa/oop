#include "WorkWithVector.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>

void PrintSortVector(std::vector <double>& numbers)
{
	std::cout << std::setprecision(2) << std::fixed;
	std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<double>(std::cout, " "));
}