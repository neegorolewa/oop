#include "Add.h"
#include <algorithm>
#include <iomanip>
#include <vector>

void DivArrayOnHalfOfMax(std::vector<double>& numbers)
{
	if (!numbers.empty())
	{
		double maxElement = *std::max_element(numbers.begin(), numbers.end());

		if (maxElement == 0)
		{
			return;
		}

		for (double& num : numbers)
		{
			num /= (maxElement / 2);
		}
	}
}