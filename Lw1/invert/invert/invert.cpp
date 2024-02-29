#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <sstream>
#include <algorithm> 
#include <cmath>
#include <iomanip>

const int SIZE_OF_MATRIX = 3;
const char SPACE = ' ';
const int NEGATIVE_SIGN = -1;
const int NEGATIVE_ZERO = -0;

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
			std::cout << std::setw(5)<< std::left << matrix[i][j];
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
			if (i != j && i < j)
			{
				std::swap(matrix[i][j], matrix[j][i]);
			}
		}
	}
}

float FindMinor(std::array<std::array<float, SIZE_OF_MATRIX>, SIZE_OF_MATRIX>& matrix, int row, int column)
{
	int count = 0;

	float values[4];

	for (int i = 0; i < SIZE_OF_MATRIX; i++)
	{
		if (i == row)
		{
			continue;
		}
		for (int j = 0; j < SIZE_OF_MATRIX; j++)
		{
			if (j != column)
			{
				values[count++] = matrix[i][j];
			}
		}
	}

	return values[0] * values[3] - values[1] * values[2];
}

std::array<std::array<float, SIZE_OF_MATRIX>, SIZE_OF_MATRIX> GetMatrixOfMinor(std::array<std::array<float, SIZE_OF_MATRIX>, SIZE_OF_MATRIX>& matrix)
{
	std::array<std::array<float, SIZE_OF_MATRIX>, SIZE_OF_MATRIX> MatrixOfMinor;

	for (int i = 0; i < SIZE_OF_MATRIX; i++)
	{
		for (int j = 0; j < SIZE_OF_MATRIX; j++)
		{
			if ((i + j) % 2 == 0)
			{
				MatrixOfMinor[i][j] = FindMinor(matrix, i, j);
			}
			else
			{
				MatrixOfMinor[i][j] = FindMinor(matrix, i, j) * NEGATIVE_SIGN;
			}
		}
	}

	return MatrixOfMinor;
}

float RoundValue(float& value)
{
	return round(value * 1000) / 1000;
}

void InvertMatrix(std::array<std::array<float, SIZE_OF_MATRIX>, SIZE_OF_MATRIX>& matrix, const float& det)
{
	matrix = GetMatrixOfMinor(matrix);

	TranspositionOfMatrix(matrix);

	for (int i = 0; i < SIZE_OF_MATRIX; i++)
	{
		for (int j = 0; j < SIZE_OF_MATRIX; j++)
		{
			matrix[i][j] = matrix[i][j] / det;
			matrix[i][j] = RoundValue(matrix[i][j]);
		}
	}
}

void ChangeNegativeZero(std::array<std::array<float, SIZE_OF_MATRIX>, SIZE_OF_MATRIX>& matrix)
{
	for (int i = 0; i < SIZE_OF_MATRIX; i++)
	{
		for (int j = 0; j < SIZE_OF_MATRIX; j++)
		{
			if (matrix[i][j] == NEGATIVE_ZERO)
			{
				matrix[i][j] = 0;
			}
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
	float determinant;

	if (!ReadMatrixFromFile(inputFile, matrix))
	{
		std::cout << "Failed to read input file\n";
		std::cout << "Input file consist of float number and size of matrix must be 3*3\n";
		std::cout << "Сheck if the input file is empty\n";
		return 1;
	}

	determinant = DefinitionOfDeterminant(matrix);
	if (determinant != 0)
	{
		determinant = RoundValue(determinant);
		InvertMatrix(matrix, determinant);
	}
	else
	{
		std::cout << "Determinant is 0, inverse matrix does not exist\n";
		return 0;
	}

	ChangeNegativeZero(matrix);

	PrintMatrix(matrix);

	return 0;
}