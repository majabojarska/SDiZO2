#pragma once
#include <iostream>
#include "TextTools.h"
#include "ValueLimits.h"

class VertexSPT
{
public:
	VertexSPT(int index, int costToReach);
	VertexSPT();
	~VertexSPT();

	int cost;
	int index;
	int previousVertexIndex;

	friend std::ostream& operator<< (std::ostream& out, VertexSPT* vertex);
	friend std::ostream& operator<< (std::ostream& out, VertexSPT vertex);

};

