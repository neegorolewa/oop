#include <iostream>
#include <cstdint>
#include <optional>
#include <fstream>
#include <string>

const std::string NUMBER_MAGIC = "MAGIC";
const std::string NUMBER_NON_MAGIC = "NON-MAGIC";

struct Args
{
    std::string inputFileName;
    std::string outputFileName;
};

//std::optional<Args> ParseArguments(int argc, char* argv[])
//{
//    if (argc != 3)
//    {
//        std::cout << "Invalid arguments count\n";
//        std::cout << "Usage: Magic_numers.exe <Input file name> <Output file name>\n";
//        return std::nullopt;
//    }
//    Args args;
//    args.inputFileName = argv[1];
//    args.outputFileName = argv[2];
//    return args;
//}
//
//std::ifstream GetInputFile(Args& args)
//{
//    std::ifstream inputFile;
//    inputFile.open(args.inputFileName);
//    if (!inputFile.is_open())
//    {
//        std::cout << "Failed to open '" << args.inputFileName << "' for reading\n";
//    }
//    return inputFile;
//}
//
//std::ofstream GetOutputFile(const Args& args)
//{
//    std::ofstream outputFile;
//    outputFile.open(args.outputFileName);
//    if (!outputFile.is_open())
//    {
//        std::cout << "Failed to open '" << args.outputFileName << "' for writing\n";
//    }
//    return outputFile;
//}

std::uint64_t SumOfDigit(uint64_t num)
{
    std::uint64_t sum = 0;
    while (num != 0)
    {
        sum += num % 10;
        num = num / 10;
    }
    return sum;
}

std::string IsMagic(uint64_t number)
{
    if ((number - SumOfDigit(number)) % 9 != 0)
    {
        return NUMBER_MAGIC ;
    }
    else
    {
        return NUMBER_NON_MAGIC;
    }
}

bool IsNonNegativeNumber(std::string line)
{
    for ()
}

int main(int argc, char* argv[])
{
    // Проверка правильности аргументов командной строки
    /*auto args = ParseArguments(argc, argv);
    if (!args)
    {
        return 1;
    }*/

    /*std::ifstream inputFile = GetInputFile(args.value());
    std::ofstream outputFile = GetOutputFile(args.value());*/

    uint64_t number;
    std::cin >> number;

    std::cout << IsMagic(number) << std::endl;

    /*if (inputFile.bad())
    {
        std::cout << "Failed to read data from input file\n";
        return 1;
    }

    if (!outputFile.flush())
    {
        std::cout << "Failed to write data to output file\n";
        return 1;
    }*/

    return 0;

}
