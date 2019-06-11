#include "AdjacencyList.h"

AdjacencyList::AdjacencyList()
{
	this->edgeListArray = nullptr;
	this->vertexAmount = 0;
}

AdjacencyList::AdjacencyList(int vertexAmount)
{
	this->vertexAmount = vertexAmount;
	this->edgeListArray = new Edge * [vertexAmount];
	for (int i = 0; i < vertexAmount; i++) {
		this->edgeListArray[i] = nullptr;
	}
}

AdjacencyList::AdjacencyList(AdjacencyList* adjacencyList) : AdjacencyList(adjacencyList->vertexAmount)
{
	for (int i = 0; i < vertexAmount; i++) {
		Edge* currentEdge = adjacencyList->edgeListArray[i];
		while (currentEdge) {

			this->addEdge(currentEdge);

			currentEdge = currentEdge->nextEdge;
		}
	}
}

AdjacencyList::~AdjacencyList()
{
	for (int i = 0; i < this->vertexAmount; i++) {
		Edge* currentEdgePointer = this->edgeListArray[i];

		while (currentEdgePointer) {
			if (currentEdgePointer->nextEdge) {
				// Zapamietuje wskaznik na nastepna krawedz i usuwam poprzednia wzgledem zapamietanej.
				currentEdgePointer = currentEdgePointer->nextEdge;
				delete currentEdgePointer->previousEdge;
			}
			else {
				// Nie istnieje nastepna krawedz, zatem usuwam obecna, czyli ostatnia w liscie.
				delete currentEdgePointer;
				break;
			}
		}
	}
	// Dealokuje pamiec zajeta przez tablice list krawedzi
	delete[] edgeListArray;
}

void AdjacencyList::addEdge(Edge* edge) {
	this->addEdge(edge->startVertexIndex, edge->endVertexIndex, edge->value);
}

bool AdjacencyList::edgeExists(int startVertexIndex, int endVertexIndex)
{
	Edge* currentEdge = edgeListArray[startVertexIndex];
	while (currentEdge) {
		if (currentEdge->endVertexIndex == endVertexIndex) {
			return true;
		}
		currentEdge = currentEdge->nextEdge;
	}
	return false;
}

void AdjacencyList::addEdge(int startVertexIndex, int endVertexIndex, int edgeValue)
{
	Edge* currentEdgePointer;

	// Pobieram wskaznik na liste sasiedztwa odpowiednia dla zadanego wierzcholka.
	currentEdgePointer = this->edgeListArray[startVertexIndex];

	if (!currentEdgePointer) {
		// Nie istnieje zadna krawedz w liscie, tworze zatem pierwsza w obszarze pamieci wskazanym przez currentEdgePointer.
		this->edgeListArray[startVertexIndex] = new Edge(startVertexIndex, endVertexIndex, edgeValue);
	}
	else {
		while (currentEdgePointer->nextEdge) {
			// Dopoki istnieje nastepna krawedz wzgledem obecnej, "przechodze do nastepnej"
			currentEdgePointer = currentEdgePointer->nextEdge;
		}
		// Docieram do konca listy, tworze nowa krawedz za ostatnia istniejaca krawedzia w liscie.
		currentEdgePointer->nextEdge = new Edge(startVertexIndex, endVertexIndex, edgeValue);
		currentEdgePointer->nextEdge->previousEdge = currentEdgePointer;
	}
}
