#include "Console.h"

Console::Console()
{
	consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Console::SetPosition(size_t row, size_t column)
{
	COORD position;
	position.Y = row;
	position.X = column;
	SetConsoleCursorPosition(consoleOutput, position);
}

void Console::Write(std::string outString)
{
	std::cout << outString;
}

void Console::Write(const char* outString)
{
	this->Write(std::string(outString));
}

void Console::Write(char outChar)
{
	this->Write(std::string(1, outChar));
}



