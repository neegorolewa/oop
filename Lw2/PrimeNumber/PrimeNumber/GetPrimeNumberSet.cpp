#include "GetPrimeNumberSet.h"

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::vector<int> isPrime(upperBound + 1, true);
	std::set<int> primesNum;

	isPrime[0] = false;

	for (int i = 2; i * i <= upperBound; ++i)
	{
		if (isPrime[i])
		{
			for (int j = i * i; j <= upperBound; j += i)
			{
				isPrime[j] = false;
			}
		}
	}

	for (int i = 2; i <= upperBound; ++i)
	{
		if (isPrime[i])
		{
			primesNum.insert(i);
		}
	}

	return primesNum;
}