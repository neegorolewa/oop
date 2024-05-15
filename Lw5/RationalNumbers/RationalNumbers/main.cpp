#include <iostream>
#include "CRational.h"

int main()
{
	{
		int a = 5, b = 6, c = 7;

		(a += b) += c;
		std::cout << a << std::endl;
	}

	std::cout << (CRational(1, 10000) < CRational(2, 10000)) << std::endl;

	//исправить ошибку, добавить в тесты!"
	{
		CRational a = 5, b = 6, c = 7;

		((a += b) += c);
		std::cout << a << std::endl;
	}

	return 0;
}