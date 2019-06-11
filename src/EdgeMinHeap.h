#pragma once
#include "Edge.h"
#include "MinHeap.h"


class EdgeMinHeap : public MinHeap
{
public:
	EdgeMinHeap(int heapSize);
	~EdgeMinHeap();
	void deleteNodes();

	Edge** edgeArray;

	void insert(Edge* edge);
	Edge* extract();
	void siftUp(int index);
	void siftDown(int index);
	void swapByIndex(int indexA, int indexB);
	
	Edge* getLeftChild(int index);
	Edge* getRightChild(int index);
	Edge* getParent(int index);

	Edge* getEdgeByIndex(int index);
	Edge* peek();
};

