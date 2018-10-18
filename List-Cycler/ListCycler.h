#pragma once
#ifndef LIST_CYCLER_H
#define LIST_CYCLER_H

#include "ScLogger.h"


struct List {
	int size = -1;
	int index = 0;
	string name = "";
	string* elements = nullptr;

	~List()
	{
		if (elements != nullptr)
		{
			//delete elements;
			elements = nullptr;
		}
	}

	void updateElements(string* in, int sizeIn)
	{
		size = sizeIn;
		if(elements != nullptr)
			delete elements;
		elements = in;
	}
};

class ListCycler
{
public:

	//ScLogger* logger;

	List scList;

	ListCycler();
	~ListCycler();

	void init();
	void LoadList();
	List BuildNewList();
	void CycleList();
	void PatternHunt();
	void FindPotentials(bool* inArr, string* inMatch, int matchSize);

	string* BuildLargerArray(string* in, int currentSize);
};

#endif