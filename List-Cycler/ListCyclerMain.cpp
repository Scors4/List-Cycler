#pragma once
#include "ListCycler.h"

ListCycler* cycler;

/*Main function: Access point.*/
int main()
{
	cycler = new ListCycler();
	cycler->init();

	delete(cycler);
	cycler = nullptr;
}