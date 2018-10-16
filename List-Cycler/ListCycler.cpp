#include "ListCycler.h"
#include <iostream>


ListCycler::ListCycler()
{
	logger = new ScLogger();
}


ListCycler::~ListCycler()
{
	delete(logger);
	logger = nullptr;
}

void ListCycler::init()
{

	cin.get();
}

int main()
{
	cycler = new ListCycler();
	cycler->init();

	delete(cycler);
	cycler = nullptr;
}