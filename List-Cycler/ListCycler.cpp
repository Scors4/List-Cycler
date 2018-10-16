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
	logger->PrintToConsole("This is a test", false, false);
	logger->PrintToConsole("This is a debug test", true, false);
	std::cin.get();
}

int main()
{
	cycler = new ListCycler();
	cycler->init();

	delete(cycler);
	cycler = nullptr;
}