#include "CyclerFileEditor.h"




CyclerFileEditor::CyclerFileEditor()
{
}


CyclerFileEditor::~CyclerFileEditor()
{
}

void CyclerFileEditor::WriteToFile(List &out)
{
	fstream outFile;
	string filename = out.name;
	BuildFilename(&filename);
	if (FileExists(filename)) {
		cout << "The file " << filename << " already exists.  Would you like to override? (Y/n)";
		string in;
		getline(cin, in);
		if (!(in.empty() || in._Equal("y") || in._Equal("Y")))
		{
			cout << "Exiting program. Please restart." << endl;
			cin.get();
			exit(0);
		}
	}

	fstream writeOut;
	writeOut.open(filename, fstream::out);

	ScLogger::PrintToLog("Opened file: " + filename + " successfully.", true, true);

	writeOut << out.name << endl;
	writeOut << out.size << endl;
	writeOut << out.index << endl;

	for (int i = 0; i < out.size; i++)
	{
		writeOut << out.elements[i] << endl;
	}

	writeOut.close();
}

void CyclerFileEditor::ExitWrite(List &out)
{
	fstream outFile;
	string filename = out.name;
	BuildFilename(&filename);
	outFile.open(filename, fstream::out);

	outFile << out.name << endl;
	outFile << out.size << endl;
	outFile << out.index << endl;

	for (int i = 0; i < out.size; i++)
	{
		outFile << out.elements[i] << endl;
	}

	outFile.close();
}

List CyclerFileEditor::ReadFromFile(string fIn)
{
	string filename = fIn;
	ScLogger::PrintToLog("List to open: " + filename, true, false);
	List tList;
	BuildFilename(&filename);

	if (!FileExists(filename))
	{
		ScLogger::PrintToConsole("File not found: " + filename, false, true);
		return tList;
	}

	fstream readIn;
	readIn.open(filename, fstream::in);

	readIn >> tList.name;
	readIn >> tList.size;
	readIn >> tList.index;

	tList.elements = new string[tList.size];

	for (int i = 0; i < tList.size; i++)
	{
		readIn >> tList.elements[i];
	}

	readIn.close();

	ScLogger::PrintToLog("File loaded successfully.", true, false);

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

void CyclerFileEditor::BuildFilename(string * filename)
{
	string temp = "lists/";
	temp.append(*filename);
	temp.append(".scl");
	*filename = temp;
}

void CyclerFileEditor::ListExistingLists()
{
	
}