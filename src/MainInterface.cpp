#include "MainInterface.h"

MainInterface::MainInterface()
{
	this->graphAlgoHandlerInterface = nullptr;
	header = string("SDiZO - Zadanie projektowe nr 2, nr indeksu: 241287");
}

void MainInterface::displayChoices()
{
	cout << "Wybierz opcje:" << endl;
	cout << "    1. Minimalne drzewo rozpinajace (MST)" << endl;
	cout << "    2. Najkrotsza sciezka" << endl;
	cout << "    0. Wyjscie" << endl;
}

void MainInterface::runChoice(int choiceNumber)
{
	switch (choiceNumber) {
	case 0:
		cout << "Zamykanie programu..." << endl;
		break;
	case 1:
		this->graphAlgoHandlerInterface = new MinimumSpanningTreeInterface();
		break;
	case 2:
		this->graphAlgoHandlerInterface = new ShortestPathInterface();
		break;
	default:
		cout << "Bledny wybor, sprobuj ponownie." << endl;
		break;
	}

	if (choiceNumber > 0 && graphAlgoHandlerInterface) {
		graphAlgoHandlerInterface->run();
		delete graphAlgoHandlerInterface;
		graphAlgoHandlerInterface = nullptr;
	}
}

void MainInterface::run()
{
	while (userChoice != 0) {
		clearConsole();
		displayVerticalSpace();
		displayHeader();
		displayChoices();
		userChoice = getNumberInput();
		clearConsole();
		runChoice(userChoice);
		if (userChoice != 0) {
			pressAnyKey();
		}
	}
}

