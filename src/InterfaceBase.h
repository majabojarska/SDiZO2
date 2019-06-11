#pragma once
#include "pch.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "TextTools.h"

using namespace std;

class InterfaceBase
{
public:
	int userChoice = -1;
	string header = "MENU";
	
	virtual void run() = 0;
	
	virtual void displayChoices() = 0;
	virtual void runChoice(int choiceNumber) = 0;
	
	int getNumberInput(string promptMessage = "");
	string getStringInput(string promptMessage = "");
	void pressAnyKey();
	
	void clearConsole();
	void displayPrompt(string promptMessage = "");
	void displayHeader();
	void displayVerticalSpace(int height = 1);
};

