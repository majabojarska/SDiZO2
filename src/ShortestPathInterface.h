#pragma once
#include "GraphAlgorithmInterface.h"
class ShortestPathInterface :
	public GraphAlgorithmInterface
{
public:
	ShortestPathInterface();
	
	VertexMinHeapSPT* resultFromMatrixGraphDijkstra;
	VertexMinHeapSPT* resultFromListGraphDijkstra;

	VertexArraySPT* resultFromMatrixGraphBellmanFord;
	VertexArraySPT* resultFromListGraphBellmanFord;

	void displayChoices();
	void runChoice(int choiceNumber);
};

