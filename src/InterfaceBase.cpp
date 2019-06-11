#include "InterfaceBase.h"

int InterfaceBase::getNumberInput(string promptMessage)
{
	displayPrompt(promptMessage);
	int choice;
	cin >> choice;
	return choice;
}

string InterfaceBase::getStringInput(string promptMessage)
{
	displayPrompt(promptMessage);
	string userInput;
	cin >> userInput;
	return userInput;
}

void InterfaceBase::pressAnyKey() {
	/*cout << "\nAby kontynuowac nacisnij dowolny klawisz...";
	(void)_getch();*/
}

void InterfaceBase::clearConsole() {
	system("CLS");
}

void InterfaceBase::displayPrompt(string promptMessage)
{
	if (promptMessage.length()) {
		cout << promptMessage << endl;
	}
	cout << ">>> ";
}

void InterfaceBase::displayHeader()
{
	cout << "            " << header << endl << endl;
}

void InterfaceBase::displayVerticalSpace(int height)
{
	for (int i = 0; i < height; i++) {
		cout << endl;
	}
}
