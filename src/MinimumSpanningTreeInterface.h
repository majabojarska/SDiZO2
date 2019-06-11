#pragma once
#include "GraphAlgorithmInterface.h"
class MinimumSpanningTreeInterface :
	public GraphAlgorithmInterface
{
public:
	MinimumSpanningTreeInterface();

	ListGraph* listGraphMST;
	MatrixGraph* matrixGraphMST;

	void displayChoices();
	void runChoice(int choiceNumber);
};

