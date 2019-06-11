#pragma once

#include "InterfaceBase.h"
#include "MatrixGraph.h"
#include "ListGraph.h"

using namespace std;

class GraphAlgorithmInterface : public InterfaceBase
{
public:
	GraphAlgorithmInterface();
	~GraphAlgorithmInterface();

	void run();
	void printWrongChoiceMessage();

	void loadFromFileToBothGraphs(string filePath, int problemType = MST_TYPE); // Domyslnie wczytuje dane tak jak dla problemu MST
	void generateRandomGraph(int vertexAmount, int graphDensityPercent, int problemType = false, int minEdgeValue = 0, int maxEdgeValue = 0);
	void getRandomGenerationParameters(int problemType = MST_TYPE);

	int startVertexIndex;
	int endVertexIndex;

	int vertexAmount;
	int graphDensity;
	
	int minEdgeValue;
	int maxEdgeValue;

	MatrixGraph* matrixGraph;
	ListGraph* listGraph;
};

