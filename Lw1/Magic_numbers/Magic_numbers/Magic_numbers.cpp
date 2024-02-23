﻿#include <iostream>
#include <cstdint>
#include <optional>
#include <fstream>
#include <string>

const std::string MESSAGE_NON_MAGIC = "NON-MAGIC";
const std::string ERROR = "ERROR";

struct Args
{
    std::string inputFileName;
    std::string outputFileName;
};

std::optional<Args> ParseArguments(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: Magic_numers.exe <Input file name> <Output file name>\n";
        return std::nullopt;
    }
    Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];
    return args;
}

std::ifstream GetInputFile(Args& args)
{
    std::ifstream inputFile;
    inputFile.open(args.inputFileName);
    if (!inputFile.is_open())
    {
        std::cout << "Failed to open '" << args.inputFileName << "' for reading\n";
    }
    return inputFile;
}

std::ofstream GetOutputFile(const Args& args)
{
    std::ofstream outputFile;
    outputFile.open(args.outputFileName);
    if (!outputFile.is_open())
    {
        std::cout << "Failed to open '" << args.outputFileName << "' for writing\n";
    }
    return outputFile;
}

bool IsNonNegativeNumber(std::string line)
{
    if (line.empty())
    {
        return false;
    }

    for (int i = 0; i < line.length(); i++)
    {
        if (!isdigit(line[i]))
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[])
{
    // Проверка правильности аргументов командной строки
    auto args = ParseArguments(argc, argv);
    if (!args)
    {
        return 1;
    }

    std::ifstream inputFile = GetInputFile(args.value());
    std::ofstream outputFile = GetOutputFile(args.value());

    std::string number;
    inputFile >> number;

    if (!IsNonNegativeNumber(number))
    {
        outputFile << ERROR << '\n';
        return 0;
    }
    else
    {
        outputFile << MESSAGE_NON_MAGIC << '\n';
        return 0;
    }

    if (inputFile.bad())
    {
        std::cout << "Failed to read data from input file\n";
        return 1;
    }

    if (!outputFile.flush())
    {
        std::cout << "Failed to write data to output file\n";
        return 1;
    }

    return 0;

}
