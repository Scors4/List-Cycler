#pragma once
#include "ScLogger.h"

template <int N>
struct List {
	int size = N;
	int index;
	string elements[N];
};

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