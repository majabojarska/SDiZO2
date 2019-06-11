#pragma once
#include "VertexSPT.h"
#include "MinHeap.h"
#include "ValueLimits.h"
#include "TextTools.h"

class VertexMinHeapSPT : public MinHeap
{
public:
	VertexMinHeapSPT(int heapSize, int startVertexIndex);
	~VertexMinHeapSPT();
	void deleteNodes();

	VertexSPT** vertexArray;

	void insert(VertexSPT* vertex);
	VertexSPT* extract();
	void siftUp(int index);
	void siftDown(int index);
	void swapByIndex(int indexA, int indexB);

	VertexSPT* getLeftChild(int index);
	VertexSPT* getRightChild(int index);
	VertexSPT* getParent(int index);
	
	int getVertexIndexInArray(int graphIndex);
	VertexSPT* peek();

	void updateVertexByIndexInGraph(int vertexIndex, int cost, int previousVertexIndex);
	void updateVertexByIndexInArray(int vertexIndexInArray, int cost, int previousVertexIndex);
	VertexSPT* getVertexByIndexInGraph(int index);
	VertexSPT* getVertexByIndexInArray(int index);
	int getVertexCost(int vertexIndex);
	int getPreviousVertexIndex(int vertexIndex);

	void printPathFromStart(std::ostream& out, int pathEndVertexIndex);

	friend std::ostream& operator<< (std::ostream& out, VertexMinHeapSPT* heap);

};

