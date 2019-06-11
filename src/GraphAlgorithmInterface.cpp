#include "GraphAlgorithmInterface.h"



GraphAlgorithmInterface::GraphAlgorithmInterface()
{
	this->matrixGraph = new MatrixGraph();
	this->listGraph = new ListGraph();
}

GraphAlgorithmInterface::~GraphAlgorithmInterface()
{
	delete this->matrixGraph;
	delete this->listGraph;
}

void GraphAlgorithmInterface::run()
{
	int userChoice;

	clearConsole();
	displayVerticalSpace();
	displayHeader();
	displayChoices();
	userChoice = getNumberInput();
	clearConsole();

	while (userChoice != 0) {
		displayVerticalSpace();
		displayHeader();
		runChoice(userChoice);
		displayChoices();
		userChoice = getNumberInput();
		clearConsole();
	}
}

void GraphAlgorithmInterface::printWrongChoiceMessage() {
	cout << "Bledny wybor, sprobuj ponownie." << endl;
}

void GraphAlgorithmInterface::loadFromFileToBothGraphs(string filePath, int problemType)
{
	this->matrixGraph->loadFromFile(filePath, problemType);
	this->listGraph->loadFromFile(filePath, problemType);
}

void GraphAlgorithmInterface::generateRandomGraph(int vertexAmount, int graphDensityPercent, int problemType, int minEdgeValue, int maxEdgeValue)
{
	string tempFileName = "." + std::to_string(rand()) + ".temp";

	this->matrixGraph->generateRandom(vertexAmount, graphDensityPercent, problemType, minEdgeValue, maxEdgeValue);
	this->matrixGraph->saveToFile(tempFileName, problemType);
	this->listGraph->loadFromFile(tempFileName, problemType);

	remove(tempFileName.c_str());
}

void GraphAlgorithmInterface::getRandomGenerationParameters(int problemType)
{
	vertexAmount = getNumberInput("Podaj liczbe wierzcholkow");
	graphDensity = getNumberInput("Podaj gestosc grafu w % (0-100)");
	minEdgeValue = getNumberInput("Podaj minimalna wage krawedzi");
	maxEdgeValue = getNumberInput("Podaj maksymalna wage krawedzi");
	if (problemType >= SPT_TYPE) {
		startVertexIndex = getNumberInput("Podaj indeks wierzcholka poczatkowego");
	}
	if (problemType == MAXFLOW_TYPE) {
		endVertexIndex = getNumberInput("Podaj indeks wierzcholka koncowego");
	}
}
