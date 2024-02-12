#include <iostream>
#include <fstream>
#include <optional>
#include <string>

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
        std::cout << "Usage: CopyFile.exe <Input file name> <Output file name>\n";
        return std::nullopt;
    }
    Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];
    return args;
}

void CopyStreams(std::ifstream& input, std::ofstream& output)
{
    // Копируем содержимое входного файла в выходной
    char ch;
    while (input.get(ch))
    {
        if (!output.put(ch))
        {
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    // Проверка правильности аргументов командной строки
    auto args = ParseArguments(argc, argv);
    if (!args)
    {
        return 1;
    }

    std::ifstream input;
    input.open(args->inputFileName);
    if (!input.is_open())
    {
        std::cout << "Failed to open '" << args->inputFileName << "' for reading\n";
        return 1;
    }

    std::ofstream output;
    output.open(args->outputFileName);
    if (!output.is_open())
    {
        std::cout << "Failed to open '" << args->outputFileName << "' for writing\n";
        return 1;
    }

    CopyStreams(input, output);

    if (input.bad())
    {
        std::cout << "Failed to read data from input file\n";
        return 1;
    }

    if (!output.flush())
    {
        std::cout << "Failed to write data to output file\n";
        return 1;
    }

    return 0;
}
