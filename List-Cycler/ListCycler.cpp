#include "ListCycler.h"
#include "CyclerFileEditor.h"
#include <iostream>
#include <algorithm>
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_SPACE 32
#define KEY_P 112
#define KEY_F 102
#define KEY_H 104
#define KEY_A 97

/*Was used to intiate the ScLogger before it was made a static class.
*/
ListCycler::ListCycler()
{
	//logger = new ScLogger();
}

/*Cleaned the logger from memory at the end of the program.
*/
ListCycler::~ListCycler()
{
	//delete(logger);
	//logger = nullptr;
}

/*Initialization call to allow ScLogger to be used as well as being a launching point
for this specific class*/
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

/*Loads a list by asking the user if they want to load an existing list or make a new one.
"list" and "List" are invalid arguments.*/
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

/*Prompts the user to input elements for the list until the user inputs the command "-end-"*/
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

/*Meat and Potatoes
Responds to up and down arrow keys to cycle through list elements.  Also takes other keystrokes as follows:
A - Append the list: adding new elements.
F - Mend a list item: Allows for corrections if a typo is found later.
P - Pattern Seek: Starts the pattern recognition portion to allow for pattern-based seek.*/
void ListCycler::CycleList()
{
	if (scList.size == -1)
		return;

	bool br = false;
	int c = 0;

	cout << "Cycling list " << scList.name << ".  Press 'H' to list keyboard shortcuts.  Press Space to end cycle." << endl;

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
			case KEY_F:
				AmmendList();
				break;
			case KEY_H:
				PrintCommands();
				break;
			case KEY_A:
				AppendList();
				break;
			case 0:
				break;
			case 224:
				continue;
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

/*Looks for a pattern given by the user in the currently loaded list.
Also provides all possible matches as the pattern is input by the user.*/
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

/*Actually looks for the inMatch array in the loaded list.  Modifies the boolean array inArr so PatternHunt is able to 
print out the found possibles and bring the index to the single match if found.*/
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

/*Increases the in array size by 10.
Copies the old array into the new, deletes the old, returns the new. Does not return new size.*/
string * ListCycler::BuildLargerArray(string * in, int currentSize)
{
	string* newArr = new string[currentSize + 10];

	for (int i = 0; i < currentSize; i++)
	{
		newArr[i] = in[i];
	}

	return newArr;
}

/*Prints commands, made a function to simplify adding further commands and definitions.*/
void ListCycler::PrintCommands()
{
	cout << "'P' -> Seek pattern." << endl <<
		"'F' -> Fix current entry." << endl <<
		"'A' -> Append current list." << endl;
}

/*Ammends a single element of the current array at the current index.  User inputs the new data for that element.*/
void ListCycler::AmmendList()
{
	cout << "Ammending index " << scList.index + 1 << ": ";
	string in;
	getline(cin, in);
	scList.elements[scList.index] = in;
	cout << "New entry for index " << scList.index + 1 << ": " << scList.elements[scList.index] << endl;
}

/*Appends the currently loaded list.
This loads a new array to the next multiple of 10 so the algorithm doesn't need to take into account size % 10*/
void ListCycler::AppendList()
{
	ScLogger::PrintToLog("Appending list " + scList.name, true, false);
	cout << "Appending " << scList.name << ": " << endl;
	int index = scList.size;
	int size = scList.size + (10 - (scList.size % 10));
	string * entries = new string[size];

	for (int i = 0; i < scList.size; i++)
	{
		entries[i] = scList.elements[i];
	}

	do
	{
		string in;
		cout << "Please enter entry " << (index + 1) << " (type -end- to end): ";
		getline(cin, in);
		if (in._Equal("-end-"))
		{
			break;
		}

		entries[index] = in;
		index++;
		if ((index % 10) == 0)
		{
			entries = BuildLargerArray(entries, index);
		}

	} while (true);

	scList.updateElements(entries, index);
	entries = nullptr;

	ScLogger::PrintToLog("End result of appending " + scList.name + ":", true, false);

	for (int i = 0; i < scList.size; i++)
	{
		ScLogger::PrintToLog("Entry " + to_string(i) + ": " + scList.elements[i], true, false);
	}

	CyclerFileEditor::WriteToFile(scList);
}