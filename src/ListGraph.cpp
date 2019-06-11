#include "pch.h"
#include "ListGraph.h"

ListGraph::ListGraph()
{
	this->edgeAmount = 0;
	this->vertexAmount = 0;
	this->adjacencyList = nullptr;
	this->remainingCapacityAdjacencyList = nullptr;
}

ListGraph::ListGraph(int vertexAmount, bool isDirected, bool isMaxFlowProblem)
{
	this->isDirected = isDirected;
	this->isMaxFlowProblem = isMaxFlowProblem;
	this->edgeAmount = 0;
	this->vertexAmount = vertexAmount;
	this->adjacencyList = new AdjacencyList(vertexAmount);
	this->remainingCapacityAdjacencyList = nullptr;
}

ListGraph::~ListGraph()
{
	delete this->adjacencyList;
}


// Zwraca ilosc krawedzi skierowanych wychodzacych z wierzcholka
int ListGraph::getVertexDegreeOut(int vertexIndex)
{
	int vertexDegreeOut = 0;
	Edge* currentEdge = this->adjacencyList->edgeListArray[vertexIndex];
	while (currentEdge) {
		vertexDegreeOut++;
		currentEdge = currentEdge->nextEdge;
	}
	return vertexDegreeOut;
}

// Zwraca ilosc krawedzi skierowanych wchodzacych do wierzcholka
int ListGraph::getVertexDegreeIn(int vertexIndex)
{
	int vertexDegreeIn = 0;
	Edge* currentEdge = nullptr;

	for (int i = 0; i < vertexAmount; i++) {
		if (i == vertexIndex) {
			continue;
		}

		currentEdge = this->adjacencyList->edgeListArray[i];
		while (currentEdge) {
			if (currentEdge->endVertexIndex == vertexIndex) {
				vertexDegreeIn++;
			}
			currentEdge = currentEdge->nextEdge;
		}
	}
	return vertexDegreeIn;
}

ListGraph* ListGraph::kruskal()
{
	ListGraph* minimumSpanningTree = new ListGraph(vertexAmount);

	// Sprawdzam, czy graf jest spojny.
	// Jezeli nie jest, to nie mozna wyznaczyc MST
	if (!this->isCoherent()) {
		std::cout << "Graf jest niespojny!" << std::endl;
		return nullptr;
	}

	// Tworze kopiec typu min przechowujacy krawedzie grafu
	EdgeMinHeap* edgeMinHeap = new EdgeMinHeap(edgeAmount * 2);

	// Dodaje kolejne krawedzie do kopca w celu sortowania
	for (int i = 0; i < vertexAmount; i++) {
		Edge* currentEdge = adjacencyList->edgeListArray[i];

		while (currentEdge) {
			if (currentEdge->startVertexIndex != currentEdge->endVertexIndex)
			{
				edgeMinHeap->insert(currentEdge);
			}
			currentEdge = currentEdge->nextEdge;
		}
	}

	// Tworze obiekt za pomoca ktorego klasyfikuje przynaleznosc wierzcholkow do roznych zbiorow rozlacznych
	VertexSet* vertexSet = new VertexSet(vertexAmount);

	// Inicjalizuje tyle zbiorow rozlacznych ile jest wierzcholkow
	// (Osobny zbior rozlaczny dla kazdego wierzcholka)
	for (int i = 0; i < vertexAmount; i++) {
		vertexSet->makeSet(i);
	}

	// Liczba krawedzi dodanych do MST
	int mstEdgeAmount = 0;

	for (int i = 0; i < vertexAmount; i++) {
		Edge* nextMstEdge;

		do {
			// Wyciagam element minimalny z kopca
			nextMstEdge = edgeMinHeap->extract();
			// Jezeli wierzcholki polaczone krawedzia nextMstEdge naleza do tego samego zbioru,
			// ignoruje te krawedz i przechodze do nastepnej w kopcu.
		} while (vertexSet->areVerticesInSameSet(nextMstEdge) && !edgeMinHeap->isEmpty());
		minimumSpanningTree->adjacencyList->addEdge(nextMstEdge);
		minimumSpanningTree->adjacencyList->addEdge(nextMstEdge->getReversed());
		vertexSet->unionSets(nextMstEdge);
		mstEdgeAmount++;

		if (mstEdgeAmount >= this->vertexAmount - 1) {
			break;
		}
	}
	delete edgeMinHeap;
	delete vertexSet;

	return minimumSpanningTree;
}

ListGraph* ListGraph::prim()
{
	ListGraph* minimumSpanningTree = new ListGraph(vertexAmount);

	if (!this->isCoherent()) {
		std::cout << "Graf jest niespojny!" << std::endl;
		return nullptr;
	}
	// Zmienna do sledzenia ilosci dodanych krawedzi do MST
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
	Edge* currentEdge = nullptr;

	for (int x = 0; x < vertexAmount; x++) {

		currentEdge = this->adjacencyList->edgeListArray[currentVertexIndex];

		while (currentEdge) {
			// Dodaje do kopca wszystkie krawedzie sasiadujace z wierzcholkiem o indeksie x
			if (currentEdge->startVertexIndex != currentEdge->endVertexIndex)
			{
				edgeMinHeap->insert(currentEdge);
			}
			// Ustawiam wskaznik na kolejna krawedz w liscie sasiedztwa dla wierzcholka o indeksie x
			currentEdge = currentEdge->nextEdge;
		}

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
		minimumSpanningTree->adjacencyList->addEdge(edgeToAddToMST);
		minimumSpanningTree->adjacencyList->addEdge(edgeToAddToMST->getReversed());
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

VertexMinHeapSPT* ListGraph::dijkstra() {
	return dijkstra(rand() % vertexAmount);
}

VertexMinHeapSPT* ListGraph::dijkstra(int startVertexIndex)
{
	// Sprawdzam, czy podany indeks wierzcholka poczatkowego jest poprawny
	if (!isVertexIndexValid(startVertexIndex)) {
		std::cout << "Podano bledny indeks wierzcholka poczatkowego (" << startVertexIndex << ")." << std::endl;
		return nullptr;
	}

	// Tworze kopiec typu min przechowujacy wierzcholki umieszczane wzgledem kosztu dotarcia do nich
	// Koszt jest przechowywany jako pole w wierzcholku.
	// Domyslnie wszystkie wierzcholki maja koszt +niesk. (stala MAX)
	VertexMinHeapSPT* vertexMinHeap = new VertexMinHeapSPT(this->vertexAmount, startVertexIndex);

	// Tworze tablice zmiennych logicznych przechowujacych "status odwiedzenia" i-tego wierzcholka
	bool* isVertexVisited = new bool[this->vertexAmount];
	// Domyslnie wszystkie sa nieodwiedzone
	memset(isVertexVisited, 0, sizeof(bool) * this->vertexAmount);

	bool allVerticesAreVisited = false;
	while (!allVerticesAreVisited && !vertexMinHeap->isEmpty())
	{
		VertexSPT* currentVertex = vertexMinHeap->extract();
		int currentVertexIndex = currentVertex->index;

		// Obecnie przetwarzana krawedz z listy sasiedztwa
		Edge* currentEdge = this->adjacencyList->edgeListArray[currentVertexIndex];

		// Aktualizuje sasiadow obecnego wierzcholka w kopcu, pod warunkiem,
		// ze nie byli odwiedzeni
		while (currentEdge) {
			// Jezeli wierzcholek nie zostal odwiedzony
			if (isVertexVisited[currentEdge->endVertexIndex] == false) {
				// Wyznaczam alternatywny koszt dla rozwazanego sasiada wynikajacy z nowego przeszukiwania
				int newVertexCost = vertexMinHeap->getVertexCost(currentVertexIndex) + currentEdge->value;
				// Jezeli alternatywny koszt jest lepszy (mniejszy) niz obecny dla wierzcholka o indeksie i, to aktualizuje
				if (vertexMinHeap->getVertexCost(currentEdge->endVertexIndex) > newVertexCost) {
					// Ustawiam rowniez poprzednika aktualizowanego sasiada na obecny wierzcholek
					vertexMinHeap->updateVertexByIndexInGraph(currentEdge->endVertexIndex, newVertexCost, currentVertexIndex);
					isVertexVisited[currentVertex->index] = true;
				}
			}
			currentEdge = currentEdge->nextEdge;
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

VertexArraySPT* ListGraph::bellmanFord() {
	return bellmanFord(rand() % vertexAmount);
}

VertexArraySPT* ListGraph::bellmanFord(int startVertexIndex)
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
				// Obecnie rozwazana krawedz z listy sasiedztwa
				Edge* currentEdge = this->adjacencyList->edgeListArray[x];
				while (currentEdge)
				{
					// Jezeli krawedz istnieje
					if (currentEdge->value > MIN) {
						// Wyznaczenie kosztu alternatywnego
						int alternativeCost = vertexArray->getVertexCostByIndex(x) + currentEdge->value;
						// Odczytanie kosztu obecnego
						int currentCost = vertexArray->getVertexCostByIndex(currentEdge->endVertexIndex);
						// Jezeli koszt alternatywny jest lepszy
						if (alternativeCost < currentCost) {
							// Koszt alternatywny jest lepszy, zatem relaksacja
							if (algorithmPassNumber == 0) {
								// Pierwszy przebieg algorytmu, relaksuje wierzcholki V-1 razy
								vertexArray->updateVertexByIndexInGraph(currentEdge->endVertexIndex, alternativeCost, x);
							}
							else { // algorithmPassNumber == 1
								// Drugi przebieg algorytmu, propaguje skutki negatywnych cykli
								vertexArray->setVertexCostByIndex(currentEdge->endVertexIndex, MIN);
							}
						}
					}

					// Przechodze do nastepnej krawedzi w liscie sasiedztwa
					currentEdge = currentEdge->nextEdge;
				}
			}
		}
	}

	return vertexArray;
}

void ListGraph::generateRandom(int vertexAmount, int graphDensityPercent, int problemType, int minEdgeValue, int maxEdgeValue)
{
	this->vertexAmount = vertexAmount;
	// Wyznaczam taka ilosc krawedzi, zeby osiagnac zadana gestosc
	this->edgeAmount = getMinDirectedEdgeAmountForCoherentGraph() + getAdditionalDirectedEdgeAmountToAchieveDensity(graphDensityPercent);
	// Alokuje pamiec na liste sasiedztwa
	this->adjacencyList = new AdjacencyList(vertexAmount);

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

		this->adjacencyList->addEdge(lastConnectedVertexIndex, vertexToConnectIndex, newEdgeValue);
		if (problemType == MST_TYPE) {
			this->adjacencyList->addEdge(vertexToConnectIndex, lastConnectedVertexIndex, newEdgeValue);
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
		if (this->adjacencyList->edgeExists(startVertexIndex, endVertexIndex)) {
			continue;
		}
		else {
			this->adjacencyList->addEdge(startVertexIndex, endVertexIndex, newEdgeValue);
			if (problemType == MST_TYPE) {
				this->adjacencyList->addEdge(endVertexIndex, startVertexIndex, newEdgeValue);
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


void ListGraph::loadFromFile(std::string pathToFile, int problemType)
{
	std::ifstream inputFileStream;
	inputFileStream.open(pathToFile, std::ios::in);

	if (!inputFileStream.good()) {
		std::cout << "Otwieranie pliku nie powiodlo sie." << std::endl;
	}

	std::string inputLine;
	getline(inputFileStream, inputLine);

	std::istringstream inputStringStream(inputLine);

	// Pobranie informacji o liczbie krawedzi i liczbie wierzcholkow z pierwszej linii
	inputStringStream >> this->edgeAmount >> this->vertexAmount;
	// Je¿eli jest to potrzebne
	// poczatkowym i koncowym na potrzeby problemu 
	// najkrotszej sciezki i problemu maks. przeplywu.
	if (problemType >= SPT_TYPE) {
		inputStringStream >> this->startVertexIndex;
	}
	if (problemType == MAXFLOW_TYPE) {
		inputStringStream >> this->endVertexIndex;
	}

	if (this->adjacencyList) {
		// Jezeli istnieje juz graf, to go usuwam
		delete this->adjacencyList;
	}
	// Tworze tablice list krawedzi o rozmiarze rownym liczbie wierzcholkow
	this->adjacencyList = new AdjacencyList(this->vertexAmount);

	for (int i = 0; i < this->edgeAmount; i++) {
		getline(inputFileStream, inputLine);
		std::istringstream inputStringStream(inputLine);

		int startVertexIndex, endVertexIndex, edgeValue;

		inputStringStream >> startVertexIndex >> endVertexIndex >> edgeValue;
		Edge* newEdge = new Edge(startVertexIndex, endVertexIndex, edgeValue);
		this->adjacencyList->addEdge(newEdge);
		if (problemType == MST_TYPE) {
			this->adjacencyList->addEdge(newEdge->getReversed());
		}
	}
	inputFileStream.close();
}

void ListGraph::saveToFile(std::string pathToFile, int problemType)
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

	for (int i = 0; i < vertexAmount; i++) {
		Edge* currentEdge = this->adjacencyList->edgeListArray[i];
		while (currentEdge) {
			outputFileStream << currentEdge->startVertexIndex << ' '
				<< currentEdge->endVertexIndex << ' '
				<< currentEdge->value << std::endl;

			currentEdge = currentEdge->nextEdge;
		}
	}
	outputFileStream.close();
}

int ListGraph::getGraphWeight()
{
	int graphWeight = 0;

	for (int i = 0; i < vertexAmount; i++) {
		Edge* currentEdge = this->adjacencyList->edgeListArray[i];

		while (currentEdge) {
			graphWeight += currentEdge->value;
			currentEdge = currentEdge->nextEdge;
		}
	}
	return graphWeight;
}

std::ostream& operator<<(std::ostream& out, ListGraph* graph)
{
	if (!graph) {
		return out;
	}

	out << TextTools::getPadding(6) << "LISTA SASIEDZTWA" << TextTools::getPadding(5) << "\"wierzcholek (waga)\"" << TextTools::getNewLines(2);

	Edge* currentEdgePointer = nullptr;

	for (int i = 0; i < graph->vertexAmount; i++) {
		out << TextTools::getCenteredString(i, 4) << " |";

		currentEdgePointer = graph->adjacencyList->edgeListArray[i];

		out << TextTools::getPadding(2) << currentEdgePointer;
		if (currentEdgePointer) {
			currentEdgePointer = currentEdgePointer->nextEdge;

			while (currentEdgePointer) {
				out << " -> " << currentEdgePointer;
				currentEdgePointer = currentEdgePointer->nextEdge;
			}
			out << " -> X";
		}
		out << std::endl;
	}
	out << std::endl;
	out << "Waga grafu: " << graph->getGraphWeight() / 2 << std::endl;

	out << std::endl;

	return out;
}
