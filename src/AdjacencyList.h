#pragma once
#include "Edge.h"

class AdjacencyList
{
public:
	AdjacencyList();
	AdjacencyList(int vertexAmount);
	AdjacencyList(AdjacencyList* adjacencyList);
	~AdjacencyList();

	void addEdge(Edge* edge);
	
	int vertexAmount;
	Edge** edgeListArray;

	bool edgeExists(int startVertexIndex, int endVertexIndex);

	void addEdge(int startVertexIndex, int endVertexIndex, int edgeValue);
};

