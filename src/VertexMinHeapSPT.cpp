#include "VertexMinHeapSPT.h"


VertexMinHeapSPT::VertexMinHeapSPT(int heapSize, int startVertexIndex) : MinHeap(heapSize)
{
	this->vertexArray = new VertexSPT * [heapSize];

	for (int i = 0; i < this->heapSize; i++) {
		this->vertexArray[i] = new VertexSPT(i, MAX);
	}
	this->nodeAmount = heapSize;
	updateVertexByIndexInGraph(startVertexIndex, 0, getPreviousVertexIndex(startVertexIndex));
}

VertexMinHeapSPT::~VertexMinHeapSPT()
{
	for (int i = 0; i < heapSize; i++) {
		delete vertexArray[i];
	}
	delete[] vertexArray;
}

void VertexMinHeapSPT::deleteNodes()
{
	for (int i = 0; i < heapSize; i++) {
		delete vertexArray[i];
	}
}

void VertexMinHeapSPT::insert(VertexSPT* vertexToInsert)
{
	int newVertexIndex = nodeAmount;
	vertexArray[newVertexIndex] = vertexToInsert;
	siftUp(newVertexIndex);
	nodeAmount++;
}

VertexSPT* VertexMinHeapSPT::extract()
{
	VertexSPT* minVertex = peek();

	swapByIndex(ROOT_INDEX, getLastLeafIndex());
	nodeAmount--;
	siftDown(ROOT_INDEX);

	return minVertex;
}

void VertexMinHeapSPT::siftUp(int index)
{
	int currentIndex = index;
	while (hasParent(currentIndex)) {
		if (getVertexByIndexInArray(currentIndex)->cost < getParent(currentIndex)->cost) {
			swapByIndex(currentIndex, getParentIndex(currentIndex));
			currentIndex = getParentIndex(currentIndex);
		}
		else {
			break;
		}
	}
}

void VertexMinHeapSPT::siftDown(int index)
{
	int currentIndex = index;
	int minChildIndex;
	while (hasRightChild(currentIndex) || hasLeftChild(currentIndex)) {
		minChildIndex = currentIndex;
		if (hasLeftChild(currentIndex) && getLeftChild(currentIndex)->cost < getVertexByIndexInArray(minChildIndex)->cost) {
			// Lewe dziecko jest mniejsze
			minChildIndex = getLeftChildIndex(currentIndex);
		}
		if (hasRightChild(currentIndex) && getRightChild(currentIndex)->cost < getVertexByIndexInArray(minChildIndex)->cost) {
			// Prawe dziecko jest mniejsze
			minChildIndex = getRightChildIndex(currentIndex);
		}

		if (minChildIndex == currentIndex) {
			return;
		}

		swapByIndex(currentIndex, minChildIndex);
		currentIndex = minChildIndex;
	}
}

void VertexMinHeapSPT::swapByIndex(int indexA, int indexB)
{
	VertexSPT* temporaryVertex = this->vertexArray[indexA];
	this->vertexArray[indexA] = this->vertexArray[indexB];
	this->vertexArray[indexB] = temporaryVertex;
}

VertexSPT* VertexMinHeapSPT::getLeftChild(int index)
{
	return this->vertexArray[getLeftChildIndex(index)];
}

VertexSPT* VertexMinHeapSPT::getRightChild(int index)
{
	return this->vertexArray[getRightChildIndex(index)];
}

VertexSPT* VertexMinHeapSPT::getParent(int index)
{
	return this->vertexArray[getParentIndex(index)];
}

VertexSPT* VertexMinHeapSPT::getVertexByIndexInGraph(int index)
{
	return this->vertexArray[getVertexIndexInArray(index)];
}

VertexSPT* VertexMinHeapSPT::getVertexByIndexInArray(int index)
{
	return this->vertexArray[index];
}

int VertexMinHeapSPT::getVertexIndexInArray(int graphIndex) {
	int foundVertexIndex = -1;
	for (int x = 0; x < heapSize; x++) {
		if (vertexArray[x]->index == graphIndex) {
			foundVertexIndex = x;
			break;
		}
	}
	return foundVertexIndex;
}

VertexSPT* VertexMinHeapSPT::peek()
{
	return this->vertexArray[ROOT_INDEX];
}

void VertexMinHeapSPT::updateVertexByIndexInGraph(int vertexIndex, int cost, int previousVertexIndex)
{
	updateVertexByIndexInArray(getVertexIndexInArray(vertexIndex), cost, previousVertexIndex);
}

void VertexMinHeapSPT::updateVertexByIndexInArray(int vertexIndexInArray, int cost, int previousVertexIndex)
{
	VertexSPT* vertexToUpdate = this->vertexArray[vertexIndexInArray];
	vertexToUpdate->cost = cost;
	vertexToUpdate->previousVertexIndex = previousVertexIndex;
	siftUp(vertexIndexInArray);
}

int VertexMinHeapSPT::getVertexCost(int vertexIndex)
{
	return vertexArray[getVertexIndexInArray(vertexIndex)]->cost;
}

int VertexMinHeapSPT::getPreviousVertexIndex(int vertexIndex)
{
	return vertexArray[getVertexIndexInArray(vertexIndex)]->previousVertexIndex;
}

void VertexMinHeapSPT::printPathFromStart(std::ostream& out, int pathEndVertexIndex)
{
	if (this->getPreviousVertexIndex(pathEndVertexIndex) == -1) {
		// Algorytm dotar³ do wierzcholka poczatkowego, koniec rekursji
		out << getVertexByIndexInGraph(pathEndVertexIndex);
		return;
	}
	printPathFromStart(out, this->getPreviousVertexIndex(pathEndVertexIndex));
	out << " -> ";
	out << getVertexByIndexInGraph(pathEndVertexIndex);
}


std::ostream& operator<<(std::ostream& out, VertexMinHeapSPT* heap)
{
	if (heap) {

		// Tytuly kolumn
		out << TextTools::getPadding(3) << TextTools::getCenteredString("INDEKS", 7) << '|';
		out << TextTools::getPadding(3) << TextTools::getCenteredString("KOSZT", 7) << '|';
		out << TextTools::getPadding(1) << "SCIEZKA" << std::endl;
		out << TextTools::getPadding(10) << '|' << TextTools::getPadding(10) << '|' << std::endl; // Linijka odstepu

		for (int x = 0; x < heap->heapSize; x++) {
			for (int y = 0; y < heap->heapSize; y++) {
				if (heap->getVertexByIndexInGraph(y)->index == x) {
					out << TextTools::getPadding(3) << TextTools::getCenteredString(x, 7) << '|'; // Indeks wierzcholka koncowego
					out << TextTools::getPadding(3) << TextTools::getCenteredString(heap->getVertexCost(x), 7) << '|'; // Koszt calkowity najkrotszej sciezki 
					out << TextTools::getPadding(1); // Padding przed sciezka
					heap->printPathFromStart(out, x); // Sciezka
					out << std::endl;
				}
			}
		}
	}
	return out;
}

