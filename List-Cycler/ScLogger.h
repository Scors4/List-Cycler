#pragma once
#ifndef SC_LOGGER_H
#define SC_LOGGER_H

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class ScLogger
{
public:
	ScLogger();
	~ScLogger();

	static void OpenLog();
	static void CloseLog();

	static void PrintToConsole(string in, bool debug, bool toLog);
	static void PrintToLog(string in, bool debug, bool toConsole);

	static void execFail(string in, int code);

private:
	static fstream* log;

	static void ShortPrintToConsole(string in);
	static void ShortPrintToLog(string in);

	static string BuildTimestamp(bool debug);
};

#endif