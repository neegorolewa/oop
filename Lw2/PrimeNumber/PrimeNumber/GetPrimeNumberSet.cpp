#include "GetPrimeNumberSet.h"

// сделать чтобы тест на 100млн запускался только в релизе, и написать в чат(ооп)
std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::vector<int> isPrime(upperBound + 1, true);
	std::set<int> primesNum;

	isPrime[0] = false;

	//почему i^2
	for (int i = 2; i * i <= upperBound; ++i)
	{
		if (isPrime[i])
		{
			// -||-
			//ускорить цикл в 2 раза
			for (int j = i * i; j <= upperBound; j += i)
			{
				isPrime[j] = false;
			}
		}
	}

	//ускорить цикл и проверить время
	for (int i = 2; i <= upperBound; ++i)
	{
		if (isPrime[i])
		{
			//прочитать про метод Insert и ускорить вставить еще !!!
			primesNum.insert(i);
		}
	}

	return primesNum;
}