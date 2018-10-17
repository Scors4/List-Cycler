#pragma once
#ifndef LIST_CYCLER_H
#define LIST_CYCLER_H

#include "ScLogger.h"


struct List {
	int size;
	int index = 0;
	string* elements;
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
};

#endif