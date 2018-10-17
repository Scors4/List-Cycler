#include "ListCycler.h"
#include <iostream>
#include <algorithm>


ListCycler::ListCycler()
{
	//logger = new ScLogger();
}


ListCycler::~ListCycler()
{
	//delete(logger);
	//logger = nullptr;
}

void ListCycler::init()
{
	ScLogger::OpenLog();
	ScLogger::PrintToLog("Initializing Cycler.", false, false);
	LoadList();
	cin.get();

	ScLogger::CloseLog();
}

void ListCycler::LoadList()
{
	cout << "Would you like to open an existing list? (Y/n): ";
	string in;
	getline(cin, in);
	transform(in.begin(), in.end(), in.begin(), ::tolower);
	if (in.empty() || in._Equal("y"))
	{
		BuildNewList();
	}
	else
	{

	}
}

void ListCycler::BuildNewList()
{
	int size = 0;
	string filename;
	string in;
	filename.append("/lists/");
	cout << "Input filename (Do not include extension): ";
	getline(cin, in);
	in.append(".scl");
	filename.append(in);

	cout << "Filename and relative location: " << filename <<"\n";
}