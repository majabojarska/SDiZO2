#include "MinHeap.h"



MinHeap::MinHeap(int heapSize)
{
	this->heapSize = heapSize;
	this->nodeAmount = 0;
}

MinHeap::~MinHeap()
{
}

int MinHeap::getLastLeafIndex()
{
	return this->nodeAmount - 1;
}

int MinHeap::getLeftChildIndex(int index)
{
	return 2 * index + 1;
}

int MinHeap::getRightChildIndex(int index)
{
	return 2 * index + 2;
}

int MinHeap::getParentIndex(int index)
{
	return (index - 1) / 2;
}


bool MinHeap::hasLeftChild(int index)
{
	return index >= 0 && getLeftChildIndex(index) < this->nodeAmount;
}

bool MinHeap::hasRightChild(int index)
{
	return index >= 0 && getRightChildIndex(index) < this->nodeAmount;
}

bool MinHeap::hasParent(int index)
{
	return index > 0 && getParentIndex(index) < nodeAmount;
}

bool MinHeap::isEmpty()
{
	return nodeAmount == 0;
}

int MinHeap::getTreeDepth()
{
	return (int)ceil(log2(this->nodeAmount)) + 1;
}

int MinHeap::getAmountOfSlotsAtLevel(int level)
{
	// Zwraca maksymalna mozliwa ilosc wierzcholkow w podanym poziomie
	// Poziomy sa indeksowane od gory, liczac od 0, do 1,2,3,4,...
	return (int)pow(2, level);
}
