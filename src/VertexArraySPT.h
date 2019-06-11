#pragma once
#include "VertexSPT.h"

class VertexArraySPT
{
public:
	VertexArraySPT(int arraySize, int startVertexIndex = -1);
	~VertexArraySPT();

	int arraySize;
	VertexSPT** vertexArray;
	VertexSPT* getVertexByIndexInGraph(int index);
	void setVertexCostByIndex(int index, int cost);
	int getVertexCostByIndex(int index);
	void updateVertexByIndexInGraph(int targetVertexIndex, int cost, int newPreviousVertexIndex);
	void setPreviousVertexIndex(int tagetVertexIndex, int newPreviousVertexIndex);

	int getPreviousVertexIndex(int index);
	void printPathFromStart(std::ostream& out, int pathEndVertexIndex);
	
	friend std::ostream& operator<< (std::ostream& out, VertexArraySPT* vertex);
};

