#pragma once
#include <iostream>
#include <Windows.h>

class Console
{
	HANDLE consoleOutput;
public:
	Console();
	void SetPosition(size_t row, size_t column);
	void Write(std::string outString);
	void Write(const char* outString);
	void Write(char outChar);
};

