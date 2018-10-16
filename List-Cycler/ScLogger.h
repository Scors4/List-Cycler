#pragma once
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class ScLogger
{
public:
	ScLogger();
	~ScLogger();

	void PrintToConsole(string in, bool debug, bool toLog);
	void PrintToLog(string in, bool debug, bool toConsole);

private:

	fstream log;

	void ShortPrintToConsole(string in);
	void ShortPrintToLog(string in);
};
