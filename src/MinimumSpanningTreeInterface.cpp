#include "pch.h"
#include "MinimumSpanningTreeInterface.h"


MinimumSpanningTreeInterface::MinimumSpanningTreeInterface()
{
	this->matrixGraphMST = nullptr;
	this->listGraphMST = nullptr;
	this->header = "WYZNACZANIE MINIMALNEGO DRZEWA ROZPINAJACEGO";
}

void MinimumSpanningTreeInterface::displayChoices()
{
	cout << "Wybierz opcje:" << endl;
	cout << "    1. Wczytaj z pliku" << endl;
	cout << "    2. Wygeneruj losowo" << endl;
	cout << "    3. Wyswietl listowo i macierzowo" << endl;
	cout << "    4. Algorytm Prima" << endl;
	cout << "    5. Algorytm Kruskala" << endl;

	cout << "    0. Wyjscie" << endl;
}

void MinimumSpanningTreeInterface::runChoice(int choiceNumber)
{
	switch (choiceNumber) {
	case 1:
		// Ladowanie z pliku
		loadFromFileToBothGraphs(getStringInput("Podaj nazwe pliku"));
		break;
	case 2:
		// Losowe generowanie
		getRandomGenerationParameters(MST_TYPE);
		
		generateRandomGraph(vertexAmount,
			graphDensity,
			MST_TYPE,
			minEdgeValue,
			maxEdgeValue);
		
		break;
	case 3:
		// Wyswietlanie
		cout << this->matrixGraph;
		cout << this->listGraph;
		break;
	case 4:
		// Prim
		cout << TextTools::getPadding(6) << "WYNIK ALGORYTMU PRIMA" << TextTools::getNewLines(2);
		
		matrixGraphMST = this->matrixGraph->prim();
		listGraphMST = this->listGraph->prim();

		cout << matrixGraphMST;
		cout << listGraphMST;

		delete matrixGraphMST;
		delete listGraphMST;

		break;
	case 5:
		// Kruskal
		matrixGraphMST = this->matrixGraph->kruskal();
		listGraphMST = this->listGraph->kruskal();

		cout << TextTools::getPadding(6) << "WYNIK ALGORYTMU KRUSKALA" << TextTools::getNewLines(2);

		cout << matrixGraphMST;
		cout << listGraphMST;

		delete matrixGraphMST;
		delete listGraphMST;

		break;
	case 0:
		// Wyjscie
		break;
	default:
		printWrongChoiceMessage();
		break;
	}
}

