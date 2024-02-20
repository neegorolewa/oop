#include <string>
#include <iostream>
#include <fstream>
#include <optional>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	std::string search;
	std::string replace;
};

std::optional<Args> ParseArguments(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: CopyFile.exe <Input file name> <Output file name> <search string> <replace string>\n";
		return std::nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.search = argv[3];
	args.replace = argv[4];
	return args;
}

std::ifstream GetInputFile(Args& args)
{
	std::ifstream inputFile;
	inputFile.open(args.inputFileName);
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open '" << args.inputFileName << "' for reading\n";
		return;
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
		return;
	}
	return outputFile;
}

// Возвращает результат замены всех вхождения строки searchString внутри строки subject на replacementString
// Если строка searchString пустая, то возвращается subject
std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	// Эта функция написана не до конца. Напишите недостающий код самостоятельно

	size_t pos = 0;
	// Результат будет записан в новую строку result, оставляя строку subject неизменной
	// Какие преимущества есть у этого способа по сравнению с алгоритмом, выполняющим
	// замену прямо в строке subject?
	std::string result;
	while (pos < subject.length())
	{
		// Находим позицию искомой строки, начиная с pos
		size_t foundPos = subject.find(searchString, pos);
		// В результирующую строку записываем текст из диапазона [pos,foundPos)
		result.append(subject, pos, foundPos - pos);

		
		// Напишите недостающий код самостоятельно, чтобы функция работала корректно
	}
	return result;
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;

	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << "\n";
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArguments(argc, argv);

	// Самостоятельно выделите код копирования содержимого файла в отдельную функцию CopyFileWithReplacement,
	// принимающую имена файлов, а также строки для поиска и замены
	// Добавьте обработку ошибок

	std::ifstream inputFile = GetInputFile(args.value());
	std::ofstream outputFile = GetOutputFile(args.value());

	std::string search = args->search;
	std::string replace = args->replace;

	CopyStreamWithReplacement(inputFile, outputFile, args->search, args->replace);
	
	outputFile.flush();

	return 0;
}