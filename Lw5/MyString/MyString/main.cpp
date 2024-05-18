#include <iostream>
#include "CMyString.h"

int main()
{

	CMyString str1("text");
	CMyString str2("text");

	if (str1 == str2)
	{
		std::cout << "true";
	}
	else
	{
		std::cout << "false";
	}

	return 0;
}