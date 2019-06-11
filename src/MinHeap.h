#pragma once
#include <cmath>

#define ROOT_INDEX 0

class MinHeap
{
public:
	MinHeap(int heapSize);
	~MinHeap();

	int nodeAmount;
	int heapSize;

	virtual void deleteNodes() = 0;

	virtual void siftUp(int index) = 0;
	virtual void siftDown(int index) = 0;
	virtual void swapByIndex(int indexA, int indexB) = 0;

	int getLastLeafIndex();

	static int getLeftChildIndex(int index);
	static int getRightChildIndex(int index);
	static int getParentIndex(int index);

	bool hasLeftChild(int index);
	bool hasRightChild(int index);
	bool hasParent(int index);

	bool isEmpty();
	int getTreeDepth();
	// Zwraca maksymalna mozliwa ilosc wierzcholkow w podanym poziomie
	int getAmountOfSlotsAtLevel(int level);
		
};

