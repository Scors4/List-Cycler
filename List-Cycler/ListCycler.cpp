#include "ListCycler.h"
#include "CyclerFileEditor.h"
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
		while (true)
		{
			string in;
			string filename = ("/lists/");
			cout << "Please enter list name: ";
			getline(cin, in);

			if (in._Equal("list") || in._Equal("List"))
			{
				continue;
			}

			filename.append(in);
			filename.append(".scl");
			scList = CyclerFileEditor::ReadFromFile(filename);
			break;
		}
	}
	else
	{
		scList = BuildNewList();
	}
}

List ListCycler::BuildNewList()
{
	int size = 0;
	List tList;

	while (true)
	{
		string filename;
		string in;
		filename.append("/lists/");
		cout << "Input new list name: ";
		getline(cin, in);

		if (in._Equal("list") || in._Equal("List"))
		{
			cout << in << " is not a valid name.  Please do not use 'list' or 'List' as a name.  Case sensitive." << endl;
			continue;
		}

		in.append(".scl");
		filename.append(in);



		break;
	}

	return tList;
}