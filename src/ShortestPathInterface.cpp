#include "pch.h"
#include "ShortestPathInterface.h"


ShortestPathInterface::ShortestPathInterface()
{
	this->matrixGraph->isDirected = true;
	this->listGraph->isDirected = true;

	this->resultFromListGraphDijkstra = nullptr;
	this->resultFromMatrixGraphDijkstra = nullptr;

	this->header = "WYZNACZANIE NAJKROTSZEJ SCIEZKI";
}

void ShortestPathInterface::displayChoices()
{
	cout << "Wybierz opcje:" << endl;
	cout << "    1. Wczytaj z pliku" << endl;
	cout << "    2. Wygeneruj losowo" << endl;
	cout << "    3. Wyswietl listowo i macierzowo" << endl;
	cout << "    4. Algorytm Dijkstry" << endl;
	cout << "    5. Algorytm Bellmana-Forda" << endl;

	cout << "    0. Wyjscie" << endl;
}

void ShortestPathInterface::runChoice(int choiceNumber)
{
	switch (choiceNumber) {
	case 1:
		// Ladowanie z pliku
		loadFromFileToBothGraphs(getStringInput("Podaj nazwe pliku"), SPT_TYPE);
		break;
	case 2:
		// Losowe generowanie
		getRandomGenerationParameters(SPT_TYPE);

		generateRandomGraph(vertexAmount,
			graphDensity,
			SPT_TYPE,
			minEdgeValue,
			maxEdgeValue);

		this->matrixGraph->startVertexIndex = startVertexIndex;
		this->listGraph->startVertexIndex = startVertexIndex;

		break;
	case 3:
		// Wyswietlanie
		cout << TextTools::getPadding(6) << "Wierzcholek poczatkowy: " << this->matrixGraph->startVertexIndex << endl;
		cout << endl;
		cout << this->matrixGraph;
		cout << this->listGraph;
		break;
	case 4:
		// Dijkstra
		cout << TextTools::getPadding(6) << "WYNIK ALGORYTMU DIJKSTRY" << TextTools::getNewLines(2);

		resultFromMatrixGraphDijkstra = this->matrixGraph->dijkstra(matrixGraph->startVertexIndex);
		resultFromListGraphDijkstra = this->listGraph->dijkstra(listGraph->startVertexIndex);

		cout << TextTools::getNewLines(1);
		cout << TextTools::getPadding(3) << "Z reprezentacji macierzowej" << TextTools::getNewLines(2);
		cout << resultFromMatrixGraphDijkstra << TextTools::getNewLines(1);

		cout << TextTools::getPadding(3) << "Z reprezentacji listowej" << TextTools::getNewLines(2);
		cout << resultFromListGraphDijkstra << TextTools::getNewLines(1);

		delete resultFromMatrixGraphDijkstra;
		delete resultFromListGraphDijkstra;

		break;
	case 5:
		// Bellman-Ford
		cout << TextTools::getPadding(6) << "WYNIK ALGORYTMU BELLMANA-FORDA" << TextTools::getNewLines(2);

		resultFromMatrixGraphBellmanFord = this->matrixGraph->bellmanFord(matrixGraph->startVertexIndex);
		resultFromListGraphBellmanFord = this->listGraph->bellmanFord(listGraph->startVertexIndex);
		cout << endl;
		cout << TextTools::getPadding(3) << "Z reprezentacji macierzowej" << TextTools::getNewLines(2);
		cout << resultFromMatrixGraphBellmanFord << TextTools::getNewLines(1);

		cout << TextTools::getPadding(3) << "Z reprezentacji listowej" << TextTools::getNewLines(2);
		cout << resultFromListGraphBellmanFord << TextTools::getNewLines(1);

		delete resultFromMatrixGraphBellmanFord;
		delete resultFromListGraphBellmanFord;

		break;
	case 0:
		break;
	default:
		printWrongChoiceMessage();
		break;
	}
}



