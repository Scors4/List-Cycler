#pragma once
#include "ScLogger.h"

class ListCycler
{
public:

	ScLogger* logger;

	ListCycler();
	~ListCycler();

	void init();
};

ListCycler* cycler;

int main();