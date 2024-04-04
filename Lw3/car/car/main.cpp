#include "Car.h"
#include "CRemoteControl.h"
#include "stdafx.h"

int main()
{
	Car car;
	
	CRemoteControl remoteControl(car, std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!remoteControl.HandleCommand())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}

	return 0;
}