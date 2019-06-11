#pragma once
#include <iostream>

#include "ValueLimits.h"

class Edge
{
public:
	Edge(int startVertexIndex, int endVertexIndex, int value = 0);
	Edge(Edge* edge);
	Edge();

	int startVertexIndex;
	int endVertexIndex;

	int value;
	int flow;

	Edge* nextEdge;
	Edge* previousEdge;
	//Edge* residualEdge;

	Edge* getReversed();

	friend std::ostream& operator<< (std::ostream& out, Edge* edge);
	friend std::ostream& operator<< (std::ostream& out, Edge edge);

};

