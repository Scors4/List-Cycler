#pragma once

#include <string>
#include <fstream>

using namespace std;

class CyclerFileEditor
{
public:
	CyclerFileEditor();
	~CyclerFileEditor();

	void WriteToFile();
	void ReadFromFile(string filename);

private:
	
	fstream listFile;
};

