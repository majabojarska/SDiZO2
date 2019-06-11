#include "pch.h"
#include "Edge.h"


Edge::Edge(int startVertexIndex, int endVertexIndex, int value)
{
	this->previousEdge = nullptr;
	this->nextEdge = nullptr;
	this->value = value;
	this->startVertexIndex = startVertexIndex;
	this->endVertexIndex = endVertexIndex;

}

Edge::Edge(Edge* edge)
{
	this->previousEdge = edge->previousEdge;
	this->nextEdge = edge->nextEdge;
	this->value = edge->value;
	this->startVertexIndex = edge->startVertexIndex;
	this->endVertexIndex = edge->endVertexIndex;
}

Edge::Edge()
{
	this->previousEdge = nullptr;
	this->nextEdge = nullptr;
	this->value = MAX;
	this->startVertexIndex = -1;
	this->endVertexIndex = -1;
}

Edge* Edge::getReversed()
{
	return new Edge(endVertexIndex, startVertexIndex, value);
}

std::ostream& operator<<(std::ostream& out, Edge* edge)
{
	if (edge) {
		out << edge->endVertexIndex << " (" << edge->value << ")";
	}
	else {
		out << "X";
	}
	return out;
}

std::ostream& operator<<(std::ostream& out, Edge edge)
{
	out << edge.endVertexIndex << " (" << edge.value << ")";
	return out;
}
