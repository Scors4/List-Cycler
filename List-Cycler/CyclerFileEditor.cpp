#include "CyclerFileEditor.h"



CyclerFileEditor::CyclerFileEditor()
{
}


CyclerFileEditor::~CyclerFileEditor()
{
}

void CyclerFileEditor::WriteToFile(string filename, List &out)
{
	fstream outFile;
	if (FileExists(filename)) {
		
	}
}

List CyclerFileEditor::ReadFromFile(string filename)
{
	ScLogger::PrintToConsole("Filename: " + filename, false, false);

	List tList;
	return tList;
}

//From Rico at 
// https://stackoverflow.com/questions/4316442/stdofstream-check-if-file-exists-before-writing
bool CyclerFileEditor::FileExists(const string filename)
{
	struct stat buf;
	if (stat(filename.c_str(), &buf) != -1)
	{
		return true;
	}
	return false;
}

void CyclerFileEditor::ListExistingLists()
{
	
}