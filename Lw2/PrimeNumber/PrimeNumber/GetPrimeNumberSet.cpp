#include "GetPrimeNumberSet.h"

// ������� ����� ���� �� 100��� ���������� ������ � ������, � �������� � ���(���)
std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::vector<int> isPrime(upperBound + 1, true);
	std::set<int> primesNum;

	isPrime[0] = false;

	//������ i^2
	for (int i = 2; i * i <= upperBound; ++i)
	{
		if (isPrime[i])
		{
			// -||-
			//�������� ���� � 2 ����
			for (int j = i * i; j <= upperBound; j += i)
			{
				isPrime[j] = false;
			}
		}
	}

	//�������� ���� � ��������� �����
	for (int i = 2; i <= upperBound; ++i)
	{
		if (isPrime[i])
		{
			//��������� ��� ����� Insert � �������� �������� ��� !!!
			primesNum.insert(i);
		}
	}

	return primesNum;
}