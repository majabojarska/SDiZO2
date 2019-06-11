#include "VertexSPT.h"

VertexSPT::VertexSPT(int index, int costToReach)
{
	this->index = index;
	this->cost = costToReach;
	this->previousVertexIndex = -1;
}

VertexSPT::VertexSPT()
{
	this->index = -1;
	this->cost = INT_MAX;
}

VertexSPT::~VertexSPT()
{
}


std::ostream& operator<<(std::ostream& out, VertexSPT* vertex)
{
	if (vertex) {
		out << vertex->index << " (";
		if (vertex->cost == MIN) {
			out << "-inf";
		}
		else if (vertex->cost == MAX) {
			out << "+inf";
		}
		else {
			out << vertex->cost;
		}
		out << ")";
	}
	else {
		out << "X";
	}
	return out;
}

std::ostream& operator<<(std::ostream& out, VertexSPT vertex)
{
	out << vertex.index << " (";
	if (vertex.cost == MIN) {
		out << "-inf";
	}
	else if (vertex.cost == MAX) {
		out << "+inf";
	}
	else {
		out << vertex.cost;
	}
	out << ")";
	return out;
}


