#include "ListCycler.h"
#include "CyclerFileEditor.h"
#include <iostream>
#include <algorithm>
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_SPACE 32
#define KEY_P 112


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
	CyclerFileEditor::ExitWrite(scList);
	cout << "Data saved successfully.  Press enter to end program:";
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
			cout << "Please enter list name: ";
			getline(cin, in);

			if (in._Equal("list") || in._Equal("List"))
			{
				cout << "Cannot list files at this time." << endl;
				continue;
			}
			
			scList = CyclerFileEditor::ReadFromFile(in);
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
		cout << "Input new list name: ";
		getline(cin, filename);

		if (filename._Equal("list") || filename._Equal("List"))
		{
			cout << filename << " is not a valid name.  Please do not use 'list' or 'List' as a name.  Case sensitive." << endl;
			continue;
		}

		string* tempArr = new string[10];
		int index = 0;

		tList.name = filename;
		cout << "Awaiting entries for list: " << filename << endl;

		while (true)
		{
			string in;
			cout << "Please enter entry " << (index + 1) <<" (type -end- to end): ";
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

		CyclerFileEditor::WriteToFile(tList);

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

	cout << "Cycling list " << scList.name << ".  Press 'P' to find a pattern.  Press Space to end cycle." << endl;

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
			case KEY_P:
				PatternHunt();
				break;
			case 0:
				break;
			default:
				//cout << c << endl;
				continue;
			}

			if (scList.index == scList.size)
				scList.index = 0;
			else if (scList.index < 0)
				scList.index = scList.size - 1;

			if (c != 0)
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

void ListCycler::PatternHunt()
{
	ScLogger::PrintToLog("Pattern hunter has been enabled.", true, false);
	bool loop = true;
	string* arr = new string[10];
	bool * potentials = new bool[scList.size];
	for (int i = 0; i < scList.size; i++)
		potentials[i] = false;

	int index = 0;
	cout << "This tool will narrow down a pattern in the currently loaded list." << endl;
	cout << "Please enter the first element: " << endl;

	string in = "";
	int c = 0;

	do
	{
		getline(cin, in);
		arr[index] = in;
		cout << "Element " << index << ": " << arr[index] << endl;
		index++;
		FindPotentials(potentials, arr, index);

		c = 0;
		int p = 0;
		for (int i = 0; i < scList.size; i++)
		{
			if (potentials[i]) { c++; p = i; }
		}

		if (c == 0)
		{
			cout << "That pattern has not been found!  Would you like to remove the last element? (y/N)";
			getline(cin, in);
			loop = false;
		}
		else if (c > 1)
		{
			cout << "Multiple matches detected.  Please add another element to narrow the following list:" << endl;
			int matchInt = 0;
			for (int i = 0; i < scList.size; i++)
			{
				if (potentials[i])
				{
					int j = 0;
					cout << "Match " << ++matchInt << ": " << endl;
					for (j; j < index; j++)
					{
						cout << "\t" << scList.elements[(i + j) % scList.size] << endl;
					}
					cout << "\t" << scList.elements[((i + j) % scList.size)] << endl;
				}
			}
		}
		else if (c == 1)
		{
			scList.index = p;
			cout << "One match detected.  Now starting at index " << scList.index + 1 << "." << endl;
			loop = false;
		}

	} while (loop);

	delete potentials;
	potentials = nullptr;

	ScLogger::PrintToLog("Pattern hunter has ended.", true, false);
}

void ListCycler::FindPotentials(bool* inArr, string* inMatch, int matchSize)
{
	ScLogger::PrintToLog("Seeking potentials now", true, false);
	for (int i = 0; i < scList.size; i++)
	{
		if (scList.elements[i]._Equal(inMatch[0]))
		{
			bool match = true;
			for (int j = 0; j < matchSize; j++)
			{
				if (!(inMatch[j]._Equal(scList.elements[((i + j) % scList.size)])))
				{
					match = false;
					break;
				}
			}

			if (match)
			{
				inArr[i] = true;
			}
			else if (inArr[i])
			{
				inArr[i] = false;
			}
		}
	}
	ScLogger::PrintToLog("Potential seeking ended.", true, false);
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