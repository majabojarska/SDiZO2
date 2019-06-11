#include "VertexArraySPT.h"



VertexArraySPT::VertexArraySPT(int arraySize, int startVertexIndex)
{
	this->arraySize = arraySize;
	this->vertexArray = new VertexSPT * [arraySize];
	for (int i = 0; i < arraySize; i++) {
		this->vertexArray[i] = new VertexSPT(i, MAX);
	}
	if (startVertexIndex >= 0 && startVertexIndex < arraySize) {
		setVertexCostByIndex(startVertexIndex, 0);
	}
}

VertexArraySPT::~VertexArraySPT()
{
	for (int i = 0; i < arraySize; i++) {
		delete vertexArray[i];
	}
	delete[] vertexArray;
}

VertexSPT* VertexArraySPT::getVertexByIndexInGraph(int index)
{
	return this->vertexArray[index];
}

void VertexArraySPT::setVertexCostByIndex(int index, int cost)
{
	this->vertexArray[index]->cost = cost;
}

int VertexArraySPT::getVertexCostByIndex(int index)
{
	return this->vertexArray[index]->cost;
}

void VertexArraySPT::updateVertexByIndexInGraph(int targetVertexIndex, int cost, int newPreviousVertexIndex)
{
	setVertexCostByIndex(targetVertexIndex, cost);
	setPreviousVertexIndex(targetVertexIndex, newPreviousVertexIndex);
}

void VertexArraySPT::setPreviousVertexIndex(int targetVertexIndex, int newPreviousVertexIndex)
{
	this->vertexArray[targetVertexIndex]->previousVertexIndex = newPreviousVertexIndex;
}

int VertexArraySPT::getPreviousVertexIndex(int index)
{
	return this->vertexArray[index]->previousVertexIndex;
}

void VertexArraySPT::printPathFromStart(std::ostream& out, int pathEndVertexIndex)
{
	if (this->getPreviousVertexIndex(pathEndVertexIndex) == -1) {
		// Algorytm dotar³ do wierzcholka poczatkowego, koniec rekursji
		out << getVertexByIndexInGraph(pathEndVertexIndex);
		return;
	}
	printPathFromStart(out, this->getPreviousVertexIndex(pathEndVertexIndex));
	out << " -> ";
	out << getVertexByIndexInGraph(pathEndVertexIndex);
}


std::ostream& operator<<(std::ostream& out, VertexArraySPT* vertexArray)
{
	if (vertexArray) {

		// Tytuly kolumn
		out << TextTools::getPadding(3) << TextTools::getCenteredString("INDEKS", 7) << '|';
		out << TextTools::getPadding(3) << TextTools::getCenteredString("KOSZT", 7) << '|';
		out << TextTools::getPadding(1) << "SCIEZKA" << std::endl;
		out << TextTools::getPadding(10) << '|' << TextTools::getPadding(10) << '|' << std::endl; // Linijka odstepu

		for (int x = 0; x < vertexArray->arraySize; x++) {
			out << TextTools::getPadding(3) << TextTools::getCenteredString(x, 7) << '|'; // Indeks wierzcholka koncowego
			out << TextTools::getPadding(3) << TextTools::getCenteredString(vertexArray->getVertexCostByIndex(x), 7) << '|'; // Koszt calkowity najkrotszej sciezki 
			out << TextTools::getPadding(1); // Padding przed sciezka
			vertexArray->printPathFromStart(out, x); // Sciezka
			out << std::endl;
		}
	}
	return out;
}
