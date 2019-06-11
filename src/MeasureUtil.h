#pragma once
#include "TimeUtils.h"
#include "MatrixGraph.h"
#include "ListGraph.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <crtdbg.h>

#define GRAPH_SIZE_AMOUNT 5
#define GRAPH_DENSITY_AMOUNT 4

class MeasureUtil
{
private:
	MeasureUtil();
public:
	~MeasureUtil();
	static MeasureUtil& getInstance();

	void run();
	void measureKruskal();
	void measurePrim();
	void measureDijkstra();
	void measureBellmanFord();
	void measureFordFulkerson();
	void resetBeforeMeasurement();
	void deleteGraphs();

	string getPrevFilePath(string fileName);
	string getNewFilePath(string fileName);

	const char separator = ';';

	// Zmienne do pomiarow
	TimeUtils timeUtilsMatrix;
	TimeUtils timeUtilsList;

	unsigned long long totalTimeMatrix;
	unsigned long long totalTimeList;

	bool isPrevFileOkMatrix = false;
	bool isPrevFileOkList = false;

	MatrixGraph* matrixGraph;
	ListGraph* listGraph;

	// Stale do pomiarow
	const int graphSizes[GRAPH_SIZE_AMOUNT] = { 10,25,50,75,100 };
	const int graphDensities[GRAPH_DENSITY_AMOUNT] = { 25,50,75,99 };
	const int testSize = 100;
	const string tempFileName = ".graph_data.temp";
	// Stale do operacji na plikach
	const string extension = "csv";

	const string resultDirectory = ".\\results\\";
};

