#pragma once
#include "Graph.h"
#include "AdjacencyList.h"

class ListGraph : public Graph
{
public:
	ListGraph();
	ListGraph(int vertexAmount, bool isDirected = false, bool isMaxFlowProblem = false);
	~ListGraph();

	AdjacencyList* adjacencyList;
	AdjacencyList* remainingCapacityAdjacencyList;

	ListGraph* kruskal();
	ListGraph* prim();

	VertexMinHeapSPT* dijkstra();
	VertexMinHeapSPT* dijkstra(int startVertexIndex);
	VertexArraySPT* bellmanFord();
	VertexArraySPT* bellmanFord(int startVertexIndex);

	void generateRandom(int vertexAmount, int graphDensityPercent, int problemType = MST_TYPE, int minEdgeValue = 1, int maxEdgeValue = 1);

	int getVertexDegreeOut(int vertexIndex);
	int getVertexDegreeIn(int vertexIndex);
	
	int DFS(int currentVertexIndex, int currentFlow);

	void loadFromFile(std::string pathToFile, int problemType = 0); // Domyslnie wczytuje jak dla MST
	void saveToFile(std::string pathToFile, int problemType = 0); // Domyslnie zapisuje jak dla MST

	friend std::ostream& operator<< (std::ostream& out, ListGraph* graph);

	int getGraphWeight();
};

