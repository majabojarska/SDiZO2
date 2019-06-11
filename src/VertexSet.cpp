#include "VertexSet.h"

VertexSet::VertexSet(int vertexAmount)
{
	this->vertexSet = new VertexForSet[vertexAmount];
}

VertexSet::~VertexSet()
{
	delete[] this->vertexSet;
}

void VertexSet::makeSet(int vertexIndex)
{
	vertexSet[vertexIndex].parent = vertexIndex;
	vertexSet[vertexIndex].rank = 0;
}

int VertexSet::findSet(int vertexIndex)
{
	if (vertexSet[vertexIndex].parent != vertexIndex) {
		vertexSet[vertexIndex].parent = findSet(vertexSet[vertexIndex].parent);
	}
	return vertexSet[vertexIndex].parent;
}

void VertexSet::unionSets(int vertexAIndex, int vertexBIndex)
{
	// Szukam korzeni poddrzew, do ktorych naleza zadane wierzcholki
	int rootA = findSet(vertexAIndex);
	int rootB = findSet(vertexBIndex);

	if (rootA != rootB) {
	// Wierzcholki naleza do roznych zbiorow rozlacznych

		if (vertexSet[rootA].rank > vertexSet[rootB].rank) {
			vertexSet[rootB].parent = rootA;
			vertexSet[rootB].rank++;
		}
		else {
			vertexSet[rootA].parent = rootB;
			vertexSet[rootA].rank++;
		}
	}
}

void VertexSet::unionSets(Edge* edge)
{
	unionSets(edge->startVertexIndex, edge->endVertexIndex);
}

bool VertexSet::areVerticesInSameSet(Edge* edge) {
	return areVerticesInSameSet(edge->startVertexIndex, edge->endVertexIndex);
}

bool VertexSet::areVerticesInSameSet(int vertexA, int vertexB)
{
	return findSet(vertexA) == findSet(vertexB);
}
