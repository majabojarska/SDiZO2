#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "TextTools.h"
#include "EdgeMinHeap.h"
#include "VertexMinHeapSPT.h"
#include "VertexSet.h"
#include "VertexArraySPT.h"
#include "DynamicArray.h"
#include "ValueLimits.h"
#include "MathTools.h"

constexpr auto MST_TYPE = 0;
constexpr auto SPT_TYPE = 1;
constexpr auto MAXFLOW_TYPE = 2;

class Graph
{
public:
	Graph();
	~Graph();

	int edgeAmount;
	int vertexAmount;

	int startVertexIndex;
	int endVertexIndex;

	bool isDirected;
	bool isMaxFlowProblem;
	bool* isVertexVisited;

	virtual void loadFromFile(std::string pathToFile, int problemType = MST_TYPE) = 0;
	virtual void saveToFile(std::string pathToFile, int problemType) = 0;

	virtual int getVertexDegreeOut(int vertexNumber) = 0;
	virtual int getVertexDegreeIn(int vertexNumber) = 0;

	bool isCoherent();
	bool arePathIndicesValid(int startVertexIndex, int endVertexIndex);
	bool isVertexIndexValid(int startVertexIndex);

	long getMinDirectedEdgeAmountForCoherentGraph();
	long getAdditionalDirectedEdgeAmountToAchieveDensity(int targetGraphDensity);
	long getMaxPossibleDirectedEdgeAmount();

	void resetVisitedVertices();

	virtual void generateRandom(int vertexAmount, int graphDensityPercent, int problemType, int minEdgeValue, int maxEdgeValue) = 0;
	void generateRandomStartVertexIndex();
	void generateRandomEndVertexIndex();

	virtual int getGraphWeight() = 0;
};

