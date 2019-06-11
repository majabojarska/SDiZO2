#pragma once
#include "Edge.h"

struct VertexForSet {
	// Indeks rodzica
	int parent;
	// Ilosc wierzcholkow w zbiorze
	int rank;
};

class VertexSet
{
public:
	VertexSet(int vertexAmount);
	~VertexSet();

	VertexForSet* vertexSet;
	
	void makeSet(int vertexIndex);
	int findSet(int vertexIndex);
	void unionSets(int a, int b);
	void unionSets(Edge* edge);
	bool areVerticesInSameSet(Edge* edge);
	bool areVerticesInSameSet(int vertexA, int vertexB);
};

