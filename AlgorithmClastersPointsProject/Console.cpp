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
	//std::cout << outString;

	unsigned long count;
	WriteConsoleA(consoleOutput, outString.c_str(), outString.size(), &count, nullptr);
}

void Console::Write(const char* outString)
{
	this->Write(std::string(outString));
}

void Console::Write(char outChar)
{
	this->Write(std::string(1, outChar));
}

void Console::WritePosition(size_t row, size_t column, std::string outString)
{
	this->SetPosition(row, column);
	this->Write(outString);
}

void Console::WritePosition(size_t row, size_t column, char outChar)
{
	this->WritePosition(row, column, std::string(1, outChar));
}

void Console::Background(Colors color)
{
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(consoleOutput, &consoleInfo);

	byte colorForeground = consoleInfo.wAttributes & 0b1111;
	byte colorBackground = color << 4;

	SetConsoleTextAttribute(consoleOutput, colorBackground | colorForeground);
}

void Console::Foreground(Colors color)
{
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(consoleOutput, &consoleInfo);

	byte colorBackground = consoleInfo.wAttributes & (0b1111 << 4);

	SetConsoleTextAttribute(consoleOutput, color | colorBackground);
}



