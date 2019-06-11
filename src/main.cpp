#include "pch.h"
#include <iostream>
#include "MainInterface.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "MeasureUtil.h"
#include <fstream>

int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand((int)time(NULL));
	(new MainInterface())->run();
	//MeasureUtil::getInstance().run();

	return 0;
}