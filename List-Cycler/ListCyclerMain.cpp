#pragma once
#include "ListCycler.h"

ListCycler* cycler;

int main()
{
	cycler = new ListCycler();
	cycler->init();

	delete(cycler);
	cycler = nullptr;
}