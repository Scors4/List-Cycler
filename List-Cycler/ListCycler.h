#pragma once
#ifndef LIST_CYCLER_H
#define LIST_CYCLER_H

#include "ScLogger.h"


struct List {
	int size;
	int index;
	string* elements;
};

class ListCycler
{
public:

	//ScLogger* logger;

	ListCycler();
	~ListCycler();

	void init();
	void LoadList();
	void BuildNewList();
};

#endif