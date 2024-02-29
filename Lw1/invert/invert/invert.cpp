#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <sstream>

const int SIZE_OF_MATRIX = 3;
const char SPACE = ' ';

bool CheckValidArguments(const int argc)
{
    if (argc != 2)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: invert.exe <matrix file>\n";
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

bool AppendDataInMatrix(std::string& line, std::array<std::array<float, SIZE_OF_MATRIX>, SIZE_OF_MATRIX>& matrix, int row)
{
	std::istringstream data(line);
	int countNumber = 0;
	float number;
	while (data >> number)
	{
		if (countNumber > 2)
		{
			return false;
		}
		matrix[row][countNumber] = number;
		countNumber++;
	}
	if (data.bad() || countNumber <= 2)
	{
		return false;
	}
	return true;
}

bool ReadMatrixFromFile(std::istream& input, std::array<std::array<float, SIZE_OF_MATRIX>, SIZE_OF_MATRIX>& matrix)
{
	std::string line;
	int row = 0;

	while (std::getline(input, line))
	{
		if (line == "")
		{
			return false;
		}
		if (row > 2)
		{
			return false;
		}
		if (!AppendDataInMatrix(line, matrix, row))
		{
			return false;
		}
		row++;
	}
	if (input.bad() || row <= 2)
	{
		return false;
	}
	return true;
}

void PrintMatrix(std::array<std::array<float, SIZE_OF_MATRIX>, SIZE_OF_MATRIX>& matrix)
{
	for (int i = 0; i < SIZE_OF_MATRIX; i++)
	{
		for (int j = 0; j < SIZE_OF_MATRIX; j++)
		{
			std::cout << matrix[i][j];
			if (j != 2)
			{
				std::cout << SPACE;
			}
		}
		if (i != 2)
		{
			std::cout << '\n';
		}
	}
}

float DefinitionOfDeterminant(std::array<std::array<float, SIZE_OF_MATRIX>, SIZE_OF_MATRIX>& matrix)
{
	float determinant = matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[1][0] * matrix[2][1] * matrix[0][2] +
		matrix[0][1] * matrix[1][2] * matrix[2][0] - matrix[0][2] * matrix[1][1] * matrix[2][0] -
		matrix[1][0] * matrix[0][1] * matrix[2][2] - matrix[0][0] * matrix[2][1] * matrix[1][2];

	return determinant;
}

void TranspositionOfMatrix(std::array<std::array<float, SIZE_OF_MATRIX>, SIZE_OF_MATRIX>& matrix)
{
	for (int i = 0; i < SIZE_OF_MATRIX; i++)
	{
		for (int j = 0; j < SIZE_OF_MATRIX; j++)
		{
			if (i != j)
		}
	}
}

int main(int argc, char* argv[])
{
	if (!CheckValidArguments(argc))
	{
		return 1;
	}

	std::ifstream inputFile = GetInputFile(argv[1]);

	std::array<std::array<float, SIZE_OF_MATRIX>, SIZE_OF_MATRIX> matrix;

	ReadMatrixFromFile(inputFile, matrix);
	PrintMatrix(matrix);
	std::cout << '\n' << DefinitionOfDeterminant(matrix);

	return 0;
}