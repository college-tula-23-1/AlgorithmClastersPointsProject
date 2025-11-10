#pragma once
#include <string>
#include <Windows.h>

enum Colors
{
	Black,
	DarkBlue,
	DarkGreen,
	DarkCyan,
	DarkRed,
	DarkMagenta,
	DarkYellow,
	Gray,
	DarkGray,
	Blue,
	Green,
	Cyan,
	Red,
	Magenta,
	Yellow,
	White
};

class Console
{
	HANDLE consoleOutput;
public:
	Console();
	void SetPosition(size_t row, size_t column);
	void Write(std::string outString);
	void Write(const char* outString);
	void Write(char outChar);

	void WritePosition(size_t row, size_t column, std::string outString);
	void WritePosition(size_t row, size_t column, char outChar);

	void Background(Colors color);
	void Foreground(Colors color);


};

