#pragma once
#include "Graph.h"

class MatrixGraph : public Graph
{
public:
	MatrixGraph(int vertexAmount, bool isDirected = false, bool isMaxFlowProblem = false);
	MatrixGraph();
	~MatrixGraph();

	int** adjacencyMatrix;
	int** remainingCapacityAdjacencyMatrix;

	MatrixGraph* kruskal();
	MatrixGraph* prim();

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
	void setEdge(Edge* edge);
	void setEdge(int startVertexIndex, int endVertexIndex, int edgeValue);

	friend std::ostream& operator<< (std::ostream& out, MatrixGraph* graph);
	int getGraphWeight();

};

