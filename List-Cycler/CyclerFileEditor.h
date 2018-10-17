#pragma once
#ifndef CYCLER_FILE_EDITOR_H
#define CYCLER_FILE_EDITOR_H

#include <string>
#include <fstream>
#include <sys/stat.h>
#include "ListCycler.h"
#include "ScLogger.h"

using namespace std;

class CyclerFileEditor
{
public:
	CyclerFileEditor();
	~CyclerFileEditor();

	static void WriteToFile(string filename, List &out);
	static List ReadFromFile(string filename);

	static void ListExistingLists();

private:
	
	static fstream listFile;

	static bool FileExists(const string filename);
};

#endif