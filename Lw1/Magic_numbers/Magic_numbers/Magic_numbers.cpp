#include <iostream>
#include <cstdint>
#include <string>

const std::string MESSAGE_NON_MAGIC = "NON-MAGIC";
const std::string ERROR = "ERROR";
const char CHAR_0 = '0';

bool CheckedArguments(int argc, char* argv[])
{
    if (argc != 1)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: Magic_numers.exe\n";
        return false;
    }
    return true;
}

bool NumberIsValid(const std::string& line)
{
    uint64_t val = 0;
    
    if (line.empty())
    {
        return false;
    }

    for (auto ch: line) 
    {
        if (!isdigit(ch)) 
        {
            return false;
        }

        if (val <= (UINT64_MAX - (ch - CHAR_0)) / 10)
        {
            val = (10 * val) + (ch - CHAR_0);
        }
        else 
        {
            return false;
        }
        
    }
    return true;
}

int main(int argc, char* argv[])
{
    // Проверка правильности аргументов командной строки
    if (!CheckedArguments(argc, argv))
    {
        return 1;
    }

    std::string number;
    std::cin >> number;

    if (!NumberIsValid(number))
    {
        std::cout << ERROR << '\n';
        return 0;
    }
    else
    { 
        std::cout << MESSAGE_NON_MAGIC << '\n';
        return 0;
    }

    if (std::cin.bad())
    {
        std::cout << "Failed to read data from input stream\n";
        return 1;
    }

    if (!std::cout.flush())
    {
        std::cout << "Failed to write data to output stream\n";
        return 1;
    }

    return 0;

}
