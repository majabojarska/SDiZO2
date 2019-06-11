#pragma once
#include "InterfaceBase.h"
#include "Interfaces.h"

class MainInterface : public InterfaceBase
{
public:
	MainInterface();

	GraphAlgorithmInterface* graphAlgoHandlerInterface;

	void displayChoices();
	void runChoice(int choiceNumber);
	void run();
};

