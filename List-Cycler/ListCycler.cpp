#include "ListCycler.h"
#include "CyclerFileEditor.h"
#include <iostream>
#include <algorithm>
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_SPACE 32


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
	CycleList();
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
			string filename = ("lists/");
			cout << "Please enter list name: ";
			getline(cin, in);

			if (in._Equal("list") || in._Equal("List"))
			{
				cout << "Cannot list files at this time." << endl;
				continue;
			}

			filename.append(in);
			filename.append(".scl");
			scList = CyclerFileEditor::ReadFromFile(filename);
			if (scList.size == -1)
			{
				continue;
			}



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
		filename.append("lists/");
		cout << "Input new list name: ";
		getline(cin, in);

		if (in._Equal("list") || in._Equal("List"))
		{
			cout << in << " is not a valid name.  Please do not use 'list' or 'List' as a name.  Case sensitive." << endl;
			continue;
		}

		in.append(".scl");
		filename.append(in);

		string* tempArr = new string[10];
		int index = 0;

		while (true)
		{
			cout << "Please enter entry " << (index + 1) <<" (enter -end- to end): ";
			getline(cin, in);
			if (in._Equal("-end-"))
			{
				break;
			}

			tempArr[index] = in;
			index++;
			if ((index % 10) == 0)
			{
				tempArr = BuildLargerArray(tempArr, index);
			}
		}

		tList.updateElements(tempArr, index);
		tempArr = nullptr;

		for (int i = 0; i < tList.size; i++)
		{
			ScLogger::PrintToLog("Element " + to_string(i) + ": " + tList.elements[i], true, false);
		}

		CyclerFileEditor::WriteToFile(filename, tList);

		break;
	}

	return tList;
}

void ListCycler::CycleList()
{
	if (scList.size == -1)
		return;

	bool br = false;
	int c = 0;

	cout << "Cycling list.  Press Space to end cycle." << endl;

	do {
		cout << "Element " << (scList.index + 1) << ": " << scList.elements[scList.index] << endl;
		while (true)
		{
			c = 0;

			switch ((c = _getch())) {
			case KEY_UP:
				scList.index++;
				break;
			case KEY_DOWN:
				scList.index--;
				break;
			case KEY_SPACE:
				br = true;
				break;
			case 0:
				break;
			default:
				continue;
			}

			if (scList.index == scList.size)
				scList.index = 0;
			else if (scList.index < 0)
				scList.index = scList.size - 1;

			if (c != 0 || br)
			{
				break;
			}
		}

		if (br)
		{
			return;
		}
	}
	while (true);
}

string * ListCycler::BuildLargerArray(string * in, int currentSize)
{
	string* newArr = new string[currentSize + 10];

	for (int i = 0; i < currentSize; i++)
	{
		newArr[i] = in[i];
	}

	return newArr;
}