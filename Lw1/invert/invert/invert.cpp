#include <iostream>
#include <fstream>
#include <string>

bool CheckValidArguments(const int argc)
{
    if (argc != 2)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: invert.exe <MAtrix file>\n";
        return false;
    }
    return true;
}

std::ifstream GetInputFile(const std::string& inputFileName)
{
	std::ifstream inputFile;
	inputFile.open(inputFileName);
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open '" << inputFileName << "' for reading\n";
	}
	return inputFile;
}

int main(int argc, char* argv[])
{
	if (!CheckValidArguments(argc))
	{
		return 1;
	}

	std::ifstream inputFile = GetInputFile(argv[1]);



	return 0;
}