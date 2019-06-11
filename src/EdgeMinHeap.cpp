#include "EdgeMinHeap.h"

EdgeMinHeap::EdgeMinHeap(int heapSize) : MinHeap(heapSize)
{
	this->edgeArray = new Edge * [heapSize];
	for (int i = 0; i < heapSize; i++) {
		this->edgeArray[i] = nullptr;
	}
}

EdgeMinHeap::~EdgeMinHeap()
{
	delete[] edgeArray;
}

void EdgeMinHeap::deleteNodes()
{
	for (int i = 0; i < heapSize; i++) {
		delete edgeArray[i];
	}
}

void EdgeMinHeap::insert(Edge* edgeToInsert)
{
	int newEdgeIndex = nodeAmount;
	edgeArray[newEdgeIndex] = edgeToInsert;
	siftUp(newEdgeIndex);
	nodeAmount++;
}

Edge* EdgeMinHeap::extract()
{
	Edge* minEdge = peek();

	swapByIndex(ROOT_INDEX, getLastLeafIndex());
	nodeAmount--;
	siftDown(ROOT_INDEX);

	return minEdge;
}

void EdgeMinHeap::siftUp(int index)
{
	int currentIndex = index;
	while (hasParent(currentIndex)) {
		if (getEdgeByIndex(currentIndex)->value < getParent(currentIndex)->value) {
			swapByIndex(currentIndex, getParentIndex(currentIndex));
			currentIndex = getParentIndex(currentIndex);
		}
		else {
			break;
		}
	}
}

void EdgeMinHeap::siftDown(int index)
{
	int currentIndex = index;
	int minChildIndex;
	while (hasRightChild(currentIndex) || hasLeftChild(currentIndex)) {
		minChildIndex = currentIndex;
		if (hasRightChild(currentIndex) && getRightChild(currentIndex)->value < getEdgeByIndex(minChildIndex)->value) {
			// Prawe dziecko jest mniejsze
			minChildIndex = getRightChildIndex(currentIndex);
		}
		if (hasLeftChild(currentIndex) && getLeftChild(currentIndex)->value < getEdgeByIndex(minChildIndex)->value) {
			// Lewe dziecko jest mniejsze
			minChildIndex = getLeftChildIndex(currentIndex);
		}

		if (minChildIndex == currentIndex) {
			return;
		}
		swapByIndex(currentIndex, minChildIndex);
		currentIndex = minChildIndex;
	}
}

void EdgeMinHeap::swapByIndex(int indexA, int indexB)
{
	Edge* temporaryEdge = this->edgeArray[indexA];
	this->edgeArray[indexA] = this->edgeArray[indexB];
	this->edgeArray[indexB] = temporaryEdge;
}

Edge* EdgeMinHeap::getLeftChild(int index)
{
	return this->edgeArray[getLeftChildIndex(index)];
}

Edge* EdgeMinHeap::getRightChild(int index)
{
	return this->edgeArray[getRightChildIndex(index)];
}

Edge* EdgeMinHeap::getParent(int index)
{
	return this->edgeArray[getParentIndex(index)];
}

Edge* EdgeMinHeap::getEdgeByIndex(int index)
{
	return this->edgeArray[index];
}

Edge* EdgeMinHeap::peek()
{
	return this->edgeArray[ROOT_INDEX];
}

