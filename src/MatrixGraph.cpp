#include "pch.h"
#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int vertexAmount, bool isDirected, bool isMaxFlowProblem) : MatrixGraph()
{
	this->isDirected = isDirected;
	this->isMaxFlowProblem = isMaxFlowProblem;
	this->vertexAmount = vertexAmount;
	this->adjacencyMatrix = new int* [vertexAmount];
	for (int i = 0; i < vertexAmount; i++) {
		this->adjacencyMatrix[i] = new int[vertexAmount];
		for (int j = 0; j < vertexAmount; j++) {
			this->adjacencyMatrix[i][j] = MIN;
		}
	}
}

MatrixGraph::MatrixGraph()
{
	this->edgeAmount = 0;
	this->vertexAmount = 0;
	this->adjacencyMatrix = nullptr;
	this->remainingCapacityAdjacencyMatrix = nullptr;
}

MatrixGraph::~MatrixGraph()
{
	if (this->adjacencyMatrix) {
		for (int i = 0; i < vertexAmount; i++) {
			delete adjacencyMatrix[i];
		}
		delete[] adjacencyMatrix;
	}
	adjacencyMatrix = nullptr;

	if (this->remainingCapacityAdjacencyMatrix) {
		for (int i = 0; i < vertexAmount; i++) {
			delete remainingCapacityAdjacencyMatrix[i];
		}
		delete[] remainingCapacityAdjacencyMatrix;
	}

	remainingCapacityAdjacencyMatrix = nullptr;
}

// Zwraca ilosc krawedzi skierowanych wychodzacych z wierzcholka
int MatrixGraph::getVertexDegreeOut(int vertexIndex)
{
	int vertexDegreeOut = 0;
	for (int i = 0; i < vertexAmount; i++) {
		if (this->adjacencyMatrix[vertexIndex][i] > MIN) {
			vertexDegreeOut++;
		}
	}
	return vertexDegreeOut;
}

// Zwraca ilosc krawedzi skierowanych wchodzacych do wierzcholka
int MatrixGraph::getVertexDegreeIn(int vertexIndex)
{
	int vertexDegreeIn = 0;
	for (int i = 0; i < vertexAmount; i++) {
		if (this->adjacencyMatrix[i][vertexIndex] > MIN) {
			vertexDegreeIn++;
		}
	}
	return vertexDegreeIn;
}

MatrixGraph* MatrixGraph::kruskal()
{
	MatrixGraph* minimumSpanningTree = new MatrixGraph(vertexAmount);

	if (!this->isCoherent()) {
		std::cout << "Graf jest niespojny!" << std::endl;
		return nullptr;
	}

	// Tworze kopiec typu min przechowujacy krawedzie grafu
	EdgeMinHeap* edgeMinHeap = new EdgeMinHeap(edgeAmount * 2);

	for (int x = 0; x < vertexAmount; x++) {
		// Dodaje kolejne krawedzie do kopca w celu sortowania
		for (int y = x; y < vertexAmount; y++) {
			if (x == y) {
				// Pomijam petle
				continue;
			}
			if (this->adjacencyMatrix[x][y] >= 0) {
				edgeMinHeap->insert(new Edge(x, y, this->adjacencyMatrix[x][y]));
			}
		}
	}

	// Tworze obiekt za pomoca ktorego klasyfikuje przynaleznosc wierzcholkow do roznych zbiorow rozlacznych
	VertexSet* vertexSet = new VertexSet(vertexAmount);

	// Inicjalizuje tyle zbiorow rozlacznych ile jest wierzcholkow
	// (Osobny zbior rozlaczny dla kazdego wierzcholka)
	for (int i = 0; i < vertexAmount; i++) {
		vertexSet->makeSet(i);
	}

	int mstEdgeAmount = 0;

	for (int i = 0; i < vertexAmount - 1; i++) {
		Edge* nextMstEdge;

		do {
			// Wyciagam element minimalny z kopca
			nextMstEdge = edgeMinHeap->extract();
			// Jezeli wierzcholki polaczone krawedzia nextMstEdge naleza do tego samego zbioru,
			// ignoruje te krawedz i przechodze do nastepnej w kopcu.
		} while (vertexSet->areVerticesInSameSet(nextMstEdge) && !edgeMinHeap->isEmpty());

		minimumSpanningTree->setEdge(nextMstEdge);
		minimumSpanningTree->setEdge(nextMstEdge->getReversed());

		vertexSet->unionSets(nextMstEdge);
		mstEdgeAmount++;

		if (mstEdgeAmount >= this->vertexAmount - 1) {
			break;
		}
	}

	edgeMinHeap->deleteNodes();
	delete edgeMinHeap;
	delete vertexSet;

	return minimumSpanningTree;
}

MatrixGraph* MatrixGraph::prim()
{
	MatrixGraph* minimumSpanningTree = new MatrixGraph(vertexAmount);
	// Zmienna do sledzenia ilosci dodanych krawedzi do MST

	if (!this->isCoherent()) {
		std::cout << "Graf jest niespojny!" << std::endl;
		return nullptr;
	}
	int edgesInMST = 0;

	// Kopiec sluzacy do sortowania krawedzi malejaco wzledem wagi
	EdgeMinHeap* edgeMinHeap = new EdgeMinHeap(edgeAmount * 2);

	// Tablica przechowujaca stan odwiedzenia wierzcholka
	bool* isVertexVisited = new bool[this->vertexAmount];
	// Ustawiam wartosci wszystkich komorek tej tablicy na 0 (false)
	memset(isVertexVisited, 0, sizeof(bool) * this->vertexAmount);

	// Wierzcholek 0 wybieram jako startowy (arbitralnie)
	int currentVertexIndex = 0;
	// Wierzcholek startowy domyslnie jest odwiedzony
	isVertexVisited[currentVertexIndex] = true;

	for (int x = 0; x < vertexAmount; x++) {

		// Tablica przechowujaca informacje na temat tego, czy wierzcholek o 
		// zadanym indeksie zostal rozwazony w aktualnym przeszukiwaniu
		bool* isVertexProcessed = new bool[this->vertexAmount];
		memset(isVertexProcessed, 0, sizeof(bool) * this->vertexAmount);
		for (int i = 0; i < vertexAmount; i++) {
			isVertexProcessed[i] = isVertexVisited[i];
		}

		// W domysle, obecny wierzcholek zostal rozwazony 
		// (inaczej mogloby dojsc do powstania petli)
		isVertexProcessed[currentVertexIndex] = true;

		/////////////////////////////////
		for (int y = 0; y < vertexAmount; y++) {
			// Rozwazam wszystkie krawedzie wynikajace z macierzy sasiedztwa dla wierzcholka o indeksie currentVertexIndex
			if (currentVertexIndex == y) {
				// Pomijam petle
				continue;
			}

			if (this->adjacencyMatrix[currentVertexIndex][y] >= 0)
			{
				int newEdgeStartVertexIndex, newEdgeEndVertexIndex;

				newEdgeStartVertexIndex = currentVertexIndex;
				newEdgeEndVertexIndex = -1;
				// Szukam sasiadow wierzcholka o indeksie currentVertexIndex
				for (int i = 0; i < vertexAmount; i++) {
					if (isVertexProcessed[i]) {
						// Pomijam wierzcholki odwiedzone, rozwazone i wierzcholek, dla ktorego szukam sasiadow, 
						// w celu unikniecia stworzenia cyklu i pominiecia niepotrzebnych iteracji.
						continue;
					}
					isVertexProcessed[i] = true;

					if (this->adjacencyMatrix[currentVertexIndex][i] >= 0) {
						newEdgeEndVertexIndex = i;
						break;
					}
				}

				if (newEdgeEndVertexIndex >= 0 && !isVertexVisited[newEdgeEndVertexIndex]) {
					// Jezeli wybrany wierzcholek koncowy nie zostal odwiedzony,
					// dodaje nowa krawedz do kopca
					Edge* newEdge = new Edge(newEdgeStartVertexIndex,
						newEdgeEndVertexIndex,
						this->adjacencyMatrix[newEdgeStartVertexIndex][newEdgeEndVertexIndex]);
					edgeMinHeap->insert(newEdge);
				}
			}
		}
		/////////////////////////////////
		delete[] isVertexProcessed;

		while (!edgeMinHeap->isEmpty() && isVertexVisited[edgeMinHeap->peek()->endVertexIndex]) {
			// Usuwam (ignoruje) krawedzie, ktore po dodaniu do MST stworza w nim cykle
			edgeMinHeap->extract();
		}

		if (edgeMinHeap->isEmpty()) {
			// Jezeli w kopcu nie ma juz zadnych krawedzi, przechodze do nastepnej iteracji,
			// poniewaz i tak nie ma co dodawac
			continue;
		}

		// Pobieram pierwsza krawedz z kopca, ktora nie stworzy cyklu w MST
		Edge* edgeToAddToMST = edgeMinHeap->extract();
		// Dodaje krawedz do MST
		minimumSpanningTree->setEdge(edgeToAddToMST);
		minimumSpanningTree->setEdge(edgeToAddToMST->getReversed());
		edgesInMST++;
		isVertexVisited[edgeToAddToMST->endVertexIndex] = true;
		// Ustawiam wierzcholek, od ktorego rozpoczne nastepne poszukiwanie, na wierzcholek koncowy dodanej krawedzi
		currentVertexIndex = edgeToAddToMST->endVertexIndex;
	}

	// Jezeli MST zostalo wyznaczone poprawnie, to musi zawierac wszystkie wierzcholki grafu,
	// zatem wszystkie wierzcholki musialy byc odwiedzone w procesie jego tworzenia.
	// W ten sposob moge ostatecznie sprawdzic, czy graf wejsciowy byl spojny.
	for (int i = 0; i < vertexAmount; i++) {
		if (!isVertexVisited[i]) {
			std::cout << "Wierzcholek " << i << " nie zostal odwiedzony. Graf wejsciowy jest niespojny." << std::endl;
		}
	}

	// Zwalniam pamiec
	delete[] isVertexVisited;
	delete edgeMinHeap;

	return minimumSpanningTree;
}

VertexMinHeapSPT* MatrixGraph::dijkstra() {
	return dijkstra(rand() % vertexAmount);
}

VertexMinHeapSPT* MatrixGraph::dijkstra(int startVertexIndex)
{
	// Sprawdzam, czy podany indeks wierzcholka poczatkowego jest poprawny
	if (!isVertexIndexValid(startVertexIndex)) {
		std::cout << "Podano bledny indeks wierzcholka poczatkowego (" << startVertexIndex << ")." << std::endl;
		return nullptr;
	}

	// Tworze kopiec typu min przechowujacy wierzcholki umieszczane wzgledem kosztu dotarcia do nich
	// Koszt jest przechowywany jako pole w wierzcholku.
	// Domyslnie wszystkie wierzcholki maja koszt +niesk. (INT_MAX)
	VertexMinHeapSPT* vertexMinHeap = new VertexMinHeapSPT(this->vertexAmount, startVertexIndex);

	// Tworze tablice zmiennych logicznych przechowujacych "status odwiedzenia" i-tego wierzcholka
	bool* isVertexVisited = new bool[this->vertexAmount];
	// Domyslnie wszystkie sa nieodwiedzone
	memset(isVertexVisited, 0, sizeof(bool) * this->vertexAmount);

	bool allVerticesAreVisited = false;

	// Szukam najkrotszej sciezki dla kazdego wierzcholka w grafie, rozpoczynajac
	// w wierzcholku o indeksie startVertexIndex
	while (!allVerticesAreVisited && !vertexMinHeap->isEmpty())
	{
		VertexSPT* currentVertex = vertexMinHeap->extract();
		int currentVertexIndex = currentVertex->index;

		// Aktualizuje sasiadow obecnego wierzcholka w kopcu, pod warunkiem,
		// ze nie byli odwiedzeni
		for (int i = 0; i < vertexAmount; i++) {
			// Je¿eli wierzcholek nie zostal odwiedzony i istnieje luk
			if (isVertexVisited[i] == false && adjacencyMatrix[currentVertexIndex][i] > MIN) {
				// Wyznaczam alternatywny koszt dla rozwazanego sasiada wynikajacy z nowego przeszukiwania
				int newVertexCost = vertexMinHeap->getVertexCost(currentVertexIndex) + adjacencyMatrix[currentVertexIndex][i];
				// Jezeli alternatywny koszt jest lepszy (mniejszy) niz obecny dla wierzcholka o indeksie i, to aktualizuje
				if (vertexMinHeap->getVertexCost(i) > newVertexCost) {
					// Ustawiam rowniez poprzednika aktualizowanego sasiada na obecny wierzcholek
					vertexMinHeap->updateVertexByIndexInGraph(i, newVertexCost, currentVertexIndex);
					isVertexVisited[currentVertex->index] = true;
				}
			}
		}

		// Wypisanie testowe kazdej iteracji
		//std::cout << vertexMinHeap << std::endl << std::endl << std::endl;

		// Sprawdzam, czy wszystkie wierzcholki zostaly odwiedzone
		allVerticesAreVisited = true;
		for (int i = 0; i < vertexAmount; i++) {
			if (!isVertexVisited[i]) {
				allVerticesAreVisited = false;
				break;
			}
		}
	}

	// Zwalniam zasoby
	delete[] isVertexVisited;

	return vertexMinHeap;
}

VertexArraySPT* MatrixGraph::bellmanFord() {
	return bellmanFord(rand() % vertexAmount);
}

VertexArraySPT* MatrixGraph::bellmanFord(int startVertexIndex)
{
	// Sprawdzam, czy podany indeks wierzcholka poczatkowego jest poprawny
	if (!isVertexIndexValid(startVertexIndex)) {
		std::cout << "Podano bledny indeks wierzcholka poczatkowego (" << startVertexIndex << ")." << std::endl;
		return nullptr;
	}

	// Obiekt sluzacy do przechowywania i aktualizowania informacji o wierzcholkach w grafie
	VertexArraySPT* vertexArray = new VertexArraySPT(this->vertexAmount, startVertexIndex);

	for (int algorithmPassNumber = 0; algorithmPassNumber < 2; algorithmPassNumber++) {
		for (int i = 0; i < vertexAmount - 1; i++) {
			// Dla wszystkich potencjalnych krawedzi
			for (int x = 0; x < vertexAmount; x++)
			{
				for (int y = 0; y < vertexAmount; y++)
				{
					// Jezeli krawedz istnieje
					if (adjacencyMatrix[x][y] > MIN) {
						// Wyznaczenie kosztu alternatywnego
						int alternativeCost = vertexArray->getVertexCostByIndex(x) + adjacencyMatrix[x][y];
						// Odczytanie kosztu obecnego
						int currentCost = vertexArray->getVertexCostByIndex(y);
						// Jezeli koszt alternatywny jest lepszy
						if (alternativeCost < currentCost) {
							// Koszt alternatywny jest lepszy, zatem relaksacja
							if (algorithmPassNumber == 0) {
								// Pierwszy przebieg algorytmu, relaksuje wierzcholki V-1 razy
								vertexArray->updateVertexByIndexInGraph(y, alternativeCost, x);
							}
							else { // algorithmPassNumber == 1
								// Drugi przebieg algorytmu, propaguje skutki negatywnych cykli
								vertexArray->setVertexCostByIndex(y, MIN);
							}
						}
					}
				}
			}
		}
	}

	return vertexArray;
}

void MatrixGraph::generateRandom(int vertexAmount, int graphDensityPercent, int problemType, int minEdgeValue, int maxEdgeValue)
{
	this->vertexAmount = vertexAmount;
	// Wyznaczam taka ilosc krawedzi, zeby osiagnac zadana gestosc
	this->edgeAmount = getMinDirectedEdgeAmountForCoherentGraph() + getAdditionalDirectedEdgeAmountToAchieveDensity(graphDensityPercent);
	if (problemType == MST_TYPE) {
		this->edgeAmount /= 2;
	}
	// Alokuje pamiec na liste sasiedztwa
	this->adjacencyMatrix = new int* [vertexAmount];
	for (int x = 0; x < vertexAmount; x++) {
		this->adjacencyMatrix[x] = new int[vertexAmount];

		for (int y = 0; y < vertexAmount; y++) {
			this->adjacencyMatrix[x][y] = MIN;
		}
	}

	int addedEdgeAmount = 0;

	int newEdgeValue;
	int newEdgeStartVertexIndex = rand() % vertexAmount;

	// Tablica dynamiczna wypelniona wierzcholkami stopnia 0
	DynamicArray* unconnectedVerticesArray = new DynamicArray();

	for (int i = 0; i < vertexAmount; i++) {
		unconnectedVerticesArray->insert(i);
	}
	int lastConnectedVertexIndex = rand() % vertexAmount;
	unconnectedVerticesArray->deleteByValue(lastConnectedVertexIndex);

	// Wypelnianie grafu krawedziami tak, aby byl spojny
	while (!unconnectedVerticesArray->isEmpty()) {
		int nextIndexInArray = rand() % unconnectedVerticesArray->getSize();

		int vertexToConnectIndex = unconnectedVerticesArray->getAtIndex(nextIndexInArray);
		unconnectedVerticesArray->deleteAtIndex(nextIndexInArray);

		newEdgeValue = minEdgeValue + rand() % maxEdgeValue;

		this->setEdge(lastConnectedVertexIndex, vertexToConnectIndex, newEdgeValue);
		if (problemType == MST_TYPE) {
			this->setEdge(vertexToConnectIndex, lastConnectedVertexIndex, newEdgeValue);
		}
		lastConnectedVertexIndex = vertexToConnectIndex;
		addedEdgeAmount++;
	}

	// Dopelnianie grafu krawedziami do osiagniecia pozadanej gestosci
	while (addedEdgeAmount < this->edgeAmount) {
		int startVertexIndex = rand() % vertexAmount;
		int endVertexIndex = rand() % vertexAmount;
		newEdgeValue = minEdgeValue + rand() % maxEdgeValue;
		// Jezeli generuje graf dla problemu MST, nie generuje petli
		if (problemType == MST_TYPE && startVertexIndex == endVertexIndex) {
			continue;
		}
		// Jezeli krawedz miedzy tymi wierzcholkami juz istnieje, to wracam do poczatku petli
		if (this->adjacencyMatrix[startVertexIndex][endVertexIndex] > MIN) {
			continue;
		}
		else {
			this->setEdge(startVertexIndex, endVertexIndex, newEdgeValue);
			if (problemType == MST_TYPE) {
				this->setEdge(endVertexIndex, startVertexIndex, newEdgeValue);
			}
		}

		addedEdgeAmount++;
	}

	if (problemType >= SPT_TYPE) {
		generateRandomStartVertexIndex();
	}
	if (problemType == MAXFLOW_TYPE) {
		generateRandomEndVertexIndex();
	}

	delete unconnectedVerticesArray;
}



void MatrixGraph::loadFromFile(std::string pathToFile, int problemType)
{
	std::ifstream inputFileStream;
	// Otwiera plik.
	inputFileStream.open(pathToFile);

	// Sprawdza, czy plik zostal pomyslnie otwarty.
	if (!inputFileStream.good()) {
		std::cout << "Otwieranie pliku nie powiodlo sie." << std::endl;
		return;
	}

	// Zmienna, do ktorej sa wczytywane kolejne linie pliku.
	std::string inputLine;
	getline(inputFileStream, inputLine);

	std::istringstream inputStringStream(inputLine);

	// Pobiera informacje o liczbie krawedzi i wierzcholkow z pierwszej linii.
	inputStringStream >> this->edgeAmount;
	inputStringStream >> this->vertexAmount;
	// Je¿eli jest to potrzebne
	// poczatkowym i koncowym na potrzeby problemu 
	// najkrotszej sciezki i problemu maks. przeplywu.

	if (problemType >= SPT_TYPE) {
		inputStringStream >> this->startVertexIndex;
	}
	if (problemType == MAXFLOW_TYPE) {
		inputStringStream >> this->endVertexIndex;
	}

	// Alokuje pamiec dla macierzy sasiedztwa.
	this->adjacencyMatrix = new int* [vertexAmount];
	for (int i = 0; i < vertexAmount; i++) {
		this->adjacencyMatrix[i] = new int[vertexAmount];
		for (int j = 0; j < vertexAmount; j++) {
			this->adjacencyMatrix[i][j] = MIN;
		}
	}

	// Wczytuje informacje o krawedziach z grafu
	for (int i = 0; i < edgeAmount; i++) {
		getline(inputFileStream, inputLine);
		std::istringstream inputStringStream(inputLine);

		int startVertexIndex, endVertexIndex, edgeValue;
		inputStringStream >> startVertexIndex;
		inputStringStream >> endVertexIndex;
		inputStringStream >> edgeValue;

		this->setEdge(startVertexIndex, endVertexIndex, edgeValue);
		if (!Graph::isDirected) {
			this->setEdge(endVertexIndex, startVertexIndex, edgeValue);
		}
	}
	inputFileStream.close();
}

void MatrixGraph::setEdge(Edge* edge) {
	this->setEdge(edge->startVertexIndex, edge->endVertexIndex, edge->value);
}

void MatrixGraph::setEdge(int startVertexIndex, int endVertexIndex, int edgeValue) {
	this->adjacencyMatrix[startVertexIndex][endVertexIndex] = edgeValue;
}

int MatrixGraph::getGraphWeight()
{
	int graphWeight = 0;
	for (int x = 0; x < vertexAmount; x++) {
		for (int y = 0; y < vertexAmount; y++) {
			if (this->adjacencyMatrix[x][y] > MIN) {
				graphWeight += this->adjacencyMatrix[x][y];
			}
		}
	}

	return graphWeight;
}

void MatrixGraph::saveToFile(std::string pathToFile, int problemType)
{
	std::ofstream outputFileStream;
	outputFileStream.open(pathToFile);

	if (!outputFileStream.good()) {
		std::cout << "Otwieranie pliku nie powiodlo sie." << std::endl;
	}

	outputFileStream << this->edgeAmount << ' ' << this->vertexAmount;
	if (problemType == SPT_TYPE) {
		outputFileStream << ' ' << this->startVertexIndex;
	}
	else if (problemType == MAXFLOW_TYPE) {
		outputFileStream << ' ' << this->endVertexIndex;
	}
	outputFileStream << std::endl;

	for (int x = 0; x < vertexAmount; x++) {
		int y = 0;
		if (problemType == MST_TYPE) {
			y = x;
		}
		for (; y < vertexAmount; y++) {
			if (this->adjacencyMatrix[x][y] > MIN) {
				outputFileStream << x << ' '
					<< y << ' '
					<< this->adjacencyMatrix[x][y] << std::endl;
			}
		}
	}

	outputFileStream.close();
}

std::ostream& operator<<(std::ostream& out, MatrixGraph* graph)
{
	if (!graph) {
		return out;
	}

	out << TextTools::getPadding(6) << "MACIERZ SASIEDZTWA" << TextTools::getNewLines(2);
	out << TextTools::getPadding(6);
	for (int i = 0; i < graph->vertexAmount; i++) {
		out << TextTools::getCenteredString(i, 6);
	}
	out << std::endl;

	out << TextTools::getPadding(5);
	for (int i = 0; i < graph->vertexAmount * 6; i++) {
		out << '_';
	}

	out << std::endl << TextTools::getPadding(5) << '|' << std::endl;

	for (int i = 0; i < graph->vertexAmount; i++) {
		out << TextTools::getCenteredString(i, 4) << " |";
		for (int j = 0; j < graph->vertexAmount; j++) {
			if (graph->adjacencyMatrix[i][j] > 0) {
				out << TextTools::getCenteredString(graph->adjacencyMatrix[i][j], 6);
			}
			else {
				out << TextTools::getCenteredString(".", 6);
			}
		}
		out << std::endl << TextTools::getPadding(5) << '|' << std::endl;
	}
	out << std::endl;
	out << "Waga grafu: " << graph->getGraphWeight() / 2 << std::endl;
	out << std::endl;
	return out;
}