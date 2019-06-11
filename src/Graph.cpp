#include "pch.h"
#include "Graph.h"

Graph::Graph()
{
	this->edgeAmount = 0;
	this->vertexAmount = 0;
	this->startVertexIndex = -1;
	this->endVertexIndex = -1;
	this->isVertexVisited = nullptr;
}

Graph::~Graph()
{

}

bool Graph::isCoherent()
{
	return edgeAmount >= vertexAmount - 1;
}

bool Graph::arePathIndicesValid(int startVertexIndex, int endVertexIndex)
{
	if (startVertexIndex < 0 || startVertexIndex >= this->vertexAmount) {
		std::cout << "Podany indeks wierzcholka poczatkowego jest bledny" << std::endl;
		return false;
	}
	if (endVertexIndex < 0 || endVertexIndex >= this->endVertexIndex) {
		std::cout << "Podany indeks wierzcholka koncowego jest bledny" << std::endl;
		return false;
	}

	return true;
}

bool Graph::isVertexIndexValid(int vertexIndex)
{
	if (vertexIndex < 0 || vertexIndex >= this->vertexAmount) {
		return false;
	}
	return true;
}

long Graph::getMinDirectedEdgeAmountForCoherentGraph()
{
	return this->vertexAmount - 1;
}

long Graph::getAdditionalDirectedEdgeAmountToAchieveDensity(int targetGraphDensity)
{
	int result = getMaxPossibleDirectedEdgeAmount();
	result -= getMinDirectedEdgeAmountForCoherentGraph();
	result *= targetGraphDensity;
	result /= 100;

	return result;
}

long Graph::getMaxPossibleDirectedEdgeAmount()
{
	return (vertexAmount * (vertexAmount - 1));
}

void Graph::resetVisitedVertices()
{
	memset(this->isVertexVisited, 0, this->vertexAmount * sizeof(bool));
}

void Graph::generateRandomStartVertexIndex()
{
	for (int i = 0; i < vertexAmount; i++) {
		if (i != endVertexIndex && getVertexDegreeOut(i) > 0) {
			startVertexIndex = i;
		}
	}
}

void Graph::generateRandomEndVertexIndex()
{
	for (int i = 0; i < vertexAmount; i++) {
		if (i != startVertexIndex && getVertexDegreeIn(i) > 0) {
			endVertexIndex = i;
		}
	}
}


