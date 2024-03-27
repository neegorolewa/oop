#include "GetPrimeNumberSet.h"

// сделать чтобы тест на 100млн запускалс€ только в релизе, и написать в чат(ооп) (¬џѕќЋЌ≈Ќќ)
std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::vector<int> isPrime(upperBound + 1, true);
	std::set<int> primesNum;

	isPrime[0] = false;

	//почему i^2 (исключаем ближайшее число не простое дл€ данного i)
	for (int i = 2; i * i <= upperBound; ++i)
	{
		if (isPrime[i])
		{
			//ускорить цикл в 2 раза (¬џѕќЋЌ≈Ќќ)

			int step = (i == 2) ? i : i * 2;

			for (int j = i * i; j <= upperBound; j += step)
			{
				isPrime[j] = false;
			}
		}
	}

	for (int i = 2; i <= upperBound; ++i)
	{
		if (isPrime[i])
		{
			//прочитать про метод Insert и ускорить вставить еще !!!(¬џѕќЋЌ≈Ќќ)
			primesNum.insert(primesNum.end(), i);
		}
	}

	return primesNum;
}