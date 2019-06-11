#include "MeasureUtil.h"

MeasureUtil::MeasureUtil()
{
	listGraph = nullptr;
	matrixGraph = nullptr;
	totalTimeList = 0;
	totalTimeMatrix = 0;
}

MeasureUtil::~MeasureUtil()
{

}

MeasureUtil& MeasureUtil::getInstance()
{
	static MeasureUtil instance;
	return instance;
}

void MeasureUtil::run()
{
	srand((unsigned int)time(NULL));
	//measureBellmanFord();
}

void MeasureUtil::measureKruskal() {

	const string fileNameMatrix = "KruskalMatrix";
	const string fileNameList = "KruskalList";

	remove(getNewFilePath(fileNameMatrix).c_str());
	remove(getPrevFilePath(fileNameMatrix).c_str());
	remove(getNewFilePath(fileNameList).c_str());
	remove(getPrevFilePath(fileNameList).c_str());

	isPrevFileOkMatrix = false;
	isPrevFileOkList = false;

	MatrixGraph* resultMatrix = nullptr;
	ListGraph* resultList = nullptr;

	ifstream prevFileMatrix;
	ofstream newFileMatrix;

	ifstream prevFileList;
	ofstream newFileList;

	// Dla kazdej gestosci
	for (int densityIndex = 0; densityIndex < GRAPH_DENSITY_AMOUNT; densityIndex++) {
		// Dla kazdej ilosci wierzcholkow
		for (int vertexAmountIndex = 0; vertexAmountIndex < GRAPH_SIZE_AMOUNT; vertexAmountIndex++) {
			prevFileMatrix.open(getPrevFilePath(fileNameMatrix));
			newFileMatrix.open(getNewFilePath(fileNameMatrix));

			prevFileList.open(getPrevFilePath(fileNameList));
			newFileList.open(getNewFilePath(fileNameList));

			if (prevFileMatrix.is_open()) {
				isPrevFileOkMatrix = true;
			}

			if (prevFileList.is_open()) {
				isPrevFileOkList = true;
			}

			string currentLineMatrix = "";
			string currentLineList = "";

			getline(prevFileMatrix, currentLineMatrix);
			getline(prevFileList, currentLineList);

			// Wprowadzam nazwy kolumn do plikow
			newFileMatrix << currentLineMatrix <<
				"V" <<
				graphSizes[vertexAmountIndex] <<
				"|D" <<
				graphDensities[densityIndex] <<
				separator << endl;

			newFileList << currentLineList
				<< "V" <<
				graphSizes[vertexAmountIndex] <<
				"|D" <<
				graphDensities[densityIndex] <<
				separator << endl;

			// Przed rozpoczeciem proby
			cout << endl << "Kruskal, density(" << graphDensities[densityIndex] << ")" <<
				", vertexAmount(" << graphSizes[vertexAmountIndex] << ")";

			// Ilosc powtorzen dla tych samych parametrow grafu
			for (int repetition = 0; repetition < testSize; repetition++) {
				// Przed rozpoczeciem pomiaru
				if (isPrevFileOkMatrix) {
					getline(prevFileMatrix, currentLineMatrix);
				}
				if (isPrevFileOkList) {
					getline(prevFileList, currentLineList);
				}

				resetBeforeMeasurement();
				deleteGraphs();

				matrixGraph = new MatrixGraph();
				listGraph = new ListGraph();

				// Generuje losowy graf (ten sam dla obu implementacji)
				matrixGraph->generateRandom(graphSizes[vertexAmountIndex], graphDensities[densityIndex], MST_TYPE, 1, 20);
				matrixGraph->saveToFile(tempFileName, MST_TYPE);
				listGraph->loadFromFile(tempFileName);
				remove(tempFileName.c_str());

				// A to takie kropki, zeby bylo widac jak pomiar postepuje w konsoli :)
				cout << '.';

				// Rozpoczynam pomiar dla macierzowej implementacji
				timeUtilsMatrix.start();
				{
					resultMatrix = matrixGraph->kruskal();
				}
				// Koncze pomiar dla macierzowej implementacji
				timeUtilsMatrix.stop();

				// Rozpoczynam pomiar dla listowej implementacji
				timeUtilsList.start();
				{
					resultList = listGraph->kruskal();
				}
				// Koncze pomiar dla listowej implementacji
				timeUtilsList.stop();

				// Po zakonczeniu pomiaru
				delete resultMatrix;
				delete resultList;

				totalTimeMatrix = timeUtilsMatrix.getDuration();
				totalTimeList = timeUtilsList.getDuration();

				//cout << "Matrix duration" << timeUtilsMatrix.getDuration() << endl;
				//cout << "List duration" << timeUtilsList.getDuration() << endl;

				newFileMatrix << currentLineMatrix << totalTimeMatrix << separator << endl;
				newFileList << currentLineList << totalTimeList << separator << endl;
			}
			newFileMatrix.close();
			prevFileMatrix.close();
			newFileList.close();
			prevFileList.close();
			prevFileMatrix.clear();
			newFileMatrix.clear();
			prevFileList.clear();
			newFileList.clear();

			remove(getPrevFilePath(fileNameMatrix).c_str());
			if (rename(getNewFilePath(fileNameMatrix).c_str(), getPrevFilePath(fileNameMatrix).c_str()) != 0) {
				cout << "Couldn't rename the file." << endl;
			}
			remove(getPrevFilePath(fileNameList).c_str());
			if (rename(getNewFilePath(fileNameList).c_str(), getPrevFilePath(fileNameList).c_str()) != 0)
			{
				cout << "Couldn't rename the file." << endl;
			}
		}
	}

	deleteGraphs();

	rename(getPrevFilePath(fileNameMatrix).c_str(), getNewFilePath(fileNameMatrix).c_str());
	rename(getPrevFilePath(fileNameList).c_str(), getNewFilePath(fileNameList).c_str());
}

void MeasureUtil::measurePrim() {

	const string fileNameMatrix = "PrimMatrix";
	const string fileNameList = "PrimList";

	remove(getNewFilePath(fileNameMatrix).c_str());
	remove(getPrevFilePath(fileNameMatrix).c_str());
	remove(getNewFilePath(fileNameList).c_str());
	remove(getPrevFilePath(fileNameList).c_str());

	isPrevFileOkMatrix = false;
	isPrevFileOkList = false;

	MatrixGraph* resultMatrix = nullptr;
	ListGraph* resultList = nullptr;

	ifstream prevFileMatrix;
	ofstream newFileMatrix;

	ifstream prevFileList;
	ofstream newFileList;

	// Dla kazdej gestosci
	for (int densityIndex = 0; densityIndex < GRAPH_DENSITY_AMOUNT; densityIndex++) {
		// Dla kazdej ilosci wierzcholkow
		for (int vertexAmountIndex = 0; vertexAmountIndex < GRAPH_SIZE_AMOUNT; vertexAmountIndex++) {
			prevFileMatrix.open(getPrevFilePath(fileNameMatrix));
			newFileMatrix.open(getNewFilePath(fileNameMatrix));

			prevFileList.open(getPrevFilePath(fileNameList));
			newFileList.open(getNewFilePath(fileNameList));

			if (prevFileMatrix.is_open()) {
				isPrevFileOkMatrix = true;
			}

			if (prevFileList.is_open()) {
				isPrevFileOkList = true;
			}

			string currentLineMatrix = "";
			string currentLineList = "";

			getline(prevFileMatrix, currentLineMatrix);
			getline(prevFileList, currentLineList);

			// Wprowadzam nazwy kolumn do plikow
			newFileMatrix << currentLineMatrix <<
				"V" <<
				graphSizes[vertexAmountIndex] <<
				"|D" <<
				graphDensities[densityIndex] <<
				separator << endl;

			newFileList << currentLineList
				<< "V" <<
				graphSizes[vertexAmountIndex] <<
				"|D" <<
				graphDensities[densityIndex] <<
				separator << endl;

			// Przed rozpoczeciem proby
			cout << endl << "Prim, density(" << graphDensities[densityIndex] << ")" <<
				", vertexAmount(" << graphSizes[vertexAmountIndex] << ")";

			// Ilosc powtorzen dla tych samych parametrow grafu
			for (int repetition = 0; repetition < testSize; repetition++) {
				// Przed rozpoczeciem pomiaru
				if (isPrevFileOkMatrix) {
					getline(prevFileMatrix, currentLineMatrix);
				}
				if (isPrevFileOkList) {
					getline(prevFileList, currentLineList);
				}

				resetBeforeMeasurement();
				deleteGraphs();

				matrixGraph = new MatrixGraph();
				listGraph = new ListGraph();

				// Generuje losowy graf (ten sam dla obu implementacji)
				matrixGraph->generateRandom(graphSizes[vertexAmountIndex], graphDensities[densityIndex], MST_TYPE, 1, 20);
				matrixGraph->saveToFile(tempFileName, MST_TYPE);
				listGraph->loadFromFile(tempFileName);
				remove(tempFileName.c_str());

				// A to takie kropki, zeby bylo widac jak pomiar postepuje w konsoli :)
				cout << '.';

				// Rozpoczynam pomiar dla macierzowej implementacji
				timeUtilsMatrix.start();
				{
					resultMatrix = matrixGraph->prim();
				}
				// Koncze pomiar dla macierzowej implementacji
				timeUtilsMatrix.stop();

				// Rozpoczynam pomiar dla listowej implementacji
				timeUtilsList.start();
				{
					resultList = listGraph->prim();
				}
				// Koncze pomiar dla listowej implementacji
				timeUtilsList.stop();

				// Po zakonczeniu pomiaru
				delete resultMatrix;
				delete resultList;

				totalTimeMatrix = timeUtilsMatrix.getDuration();
				totalTimeList = timeUtilsList.getDuration();

				//cout << "Matrix duration" << timeUtilsMatrix.getDuration() << endl;
				//cout << "List duration" << timeUtilsList.getDuration() << endl;

				newFileMatrix << currentLineMatrix << totalTimeMatrix << separator << endl;
				newFileList << currentLineList << totalTimeList << separator << endl;
			}
			newFileMatrix.close();
			prevFileMatrix.close();
			newFileList.close();
			prevFileList.close();
			prevFileMatrix.clear();
			newFileMatrix.clear();
			prevFileList.clear();
			newFileList.clear();

			remove(getPrevFilePath(fileNameMatrix).c_str());
			if (rename(getNewFilePath(fileNameMatrix).c_str(), getPrevFilePath(fileNameMatrix).c_str()) != 0) {
				cout << "Couldn't rename the file." << endl;
			}
			remove(getPrevFilePath(fileNameList).c_str());
			if (rename(getNewFilePath(fileNameList).c_str(), getPrevFilePath(fileNameList).c_str()) != 0)
			{
				cout << "Couldn't rename the file." << endl;
			}
		}
	}

	deleteGraphs();

	rename(getPrevFilePath(fileNameMatrix).c_str(), getNewFilePath(fileNameMatrix).c_str());
	rename(getPrevFilePath(fileNameList).c_str(), getNewFilePath(fileNameList).c_str());
}

void MeasureUtil::measureDijkstra() {
	const string fileNameMatrix = "DijkstraMatrix";
	const string fileNameList = "DijkstraList";

	remove(getNewFilePath(fileNameMatrix).c_str());
	remove(getPrevFilePath(fileNameMatrix).c_str());
	remove(getNewFilePath(fileNameList).c_str());
	remove(getPrevFilePath(fileNameList).c_str());

	isPrevFileOkMatrix = false;
	isPrevFileOkList = false;

	MatrixGraph* resultMatrix = nullptr;
	ListGraph* resultList = nullptr;

	ifstream prevFileMatrix;
	ofstream newFileMatrix;

	ifstream prevFileList;
	ofstream newFileList;

	// Dla kazdej gestosci
	for (int densityIndex = 0; densityIndex < GRAPH_DENSITY_AMOUNT; densityIndex++) {
		// Dla kazdej ilosci wierzcholkow
		for (int vertexAmountIndex = 0; vertexAmountIndex < GRAPH_SIZE_AMOUNT; vertexAmountIndex++) {
			prevFileMatrix.open(getPrevFilePath(fileNameMatrix));
			newFileMatrix.open(getNewFilePath(fileNameMatrix));

			prevFileList.open(getPrevFilePath(fileNameList));
			newFileList.open(getNewFilePath(fileNameList));

			if (prevFileMatrix.is_open()) {
				isPrevFileOkMatrix = true;
			}

			if (prevFileList.is_open()) {
				isPrevFileOkList = true;
			}

			string currentLineMatrix = "";
			string currentLineList = "";

			getline(prevFileMatrix, currentLineMatrix);
			getline(prevFileList, currentLineList);

			// Wprowadzam nazwy kolumn do plikow
			newFileMatrix << currentLineMatrix <<
				"V" <<
				graphSizes[vertexAmountIndex] <<
				"|D" <<
				graphDensities[densityIndex] <<
				separator << endl;

			newFileList << currentLineList
				<< "V" <<
				graphSizes[vertexAmountIndex] <<
				"|D" <<
				graphDensities[densityIndex] <<
				separator << endl;

			// Przed rozpoczeciem proby
			cout << endl << "Dijkstra, density(" << graphDensities[densityIndex] << ")" <<
				", vertexAmount(" << graphSizes[vertexAmountIndex] << ")";

			// Ilosc powtorzen dla tych samych parametrow grafu
			for (int repetition = 0; repetition < testSize; repetition++) {
				// Przed rozpoczeciem pomiaru
				if (isPrevFileOkMatrix) {
					getline(prevFileMatrix, currentLineMatrix);
				}
				if (isPrevFileOkList) {
					getline(prevFileList, currentLineList);
				}

				resetBeforeMeasurement();
				deleteGraphs();

				matrixGraph = new MatrixGraph();
				listGraph = new ListGraph();

				// Generuje losowy graf (ten sam dla obu implementacji)
				matrixGraph->generateRandom(graphSizes[vertexAmountIndex], graphDensities[densityIndex], MST_TYPE, 1, 20);
				matrixGraph->saveToFile(tempFileName, MST_TYPE);
				listGraph->loadFromFile(tempFileName);
				remove(tempFileName.c_str());

				// A to takie kropki, zeby bylo widac jak pomiar postepuje w konsoli :)
				cout << '.';

				// Rozpoczynam pomiar dla macierzowej implementacji
				timeUtilsMatrix.start();
				{
					matrixGraph->dijkstra();
				}
				// Koncze pomiar dla macierzowej implementacji
				timeUtilsMatrix.stop();

				// Rozpoczynam pomiar dla listowej implementacji
				timeUtilsList.start();
				{
					listGraph->dijkstra();
				}
				// Koncze pomiar dla listowej implementacji
				timeUtilsList.stop();

				// Po zakonczeniu pomiaru
				delete resultMatrix;
				delete resultList;

				totalTimeMatrix = timeUtilsMatrix.getDuration();
				totalTimeList = timeUtilsList.getDuration();

				//cout << "Matrix duration" << timeUtilsMatrix.getDuration() << endl;
				//cout << "List duration" << timeUtilsList.getDuration() << endl;

				newFileMatrix << currentLineMatrix << totalTimeMatrix << separator << endl;
				newFileList << currentLineList << totalTimeList << separator << endl;
			}
			newFileMatrix.close();
			prevFileMatrix.close();
			newFileList.close();
			prevFileList.close();
			prevFileMatrix.clear();
			newFileMatrix.clear();
			prevFileList.clear();
			newFileList.clear();

			remove(getPrevFilePath(fileNameMatrix).c_str());
			if (rename(getNewFilePath(fileNameMatrix).c_str(), getPrevFilePath(fileNameMatrix).c_str()) != 0) {
				cout << "Couldn't rename the file." << endl;
			}
			remove(getPrevFilePath(fileNameList).c_str());
			if (rename(getNewFilePath(fileNameList).c_str(), getPrevFilePath(fileNameList).c_str()) != 0)
			{
				cout << "Couldn't rename the file." << endl;
			}
		}
	}

	deleteGraphs();

	rename(getPrevFilePath(fileNameMatrix).c_str(), getNewFilePath(fileNameMatrix).c_str());
	rename(getPrevFilePath(fileNameList).c_str(), getNewFilePath(fileNameList).c_str());
}

void MeasureUtil::measureBellmanFord() {
	const string fileNameMatrix = "BellmanFordMatrix";
	const string fileNameList = "BellmanFordList";

	remove(getNewFilePath(fileNameMatrix).c_str());
	remove(getPrevFilePath(fileNameMatrix).c_str());
	remove(getNewFilePath(fileNameList).c_str());
	remove(getPrevFilePath(fileNameList).c_str());

	isPrevFileOkMatrix = false;
	isPrevFileOkList = false;

	MatrixGraph* resultMatrix = nullptr;
	ListGraph* resultList = nullptr;

	ifstream prevFileMatrix;
	ofstream newFileMatrix;

	ifstream prevFileList;
	ofstream newFileList;

	// Dla kazdej gestosci
	for (int densityIndex = 0; densityIndex < GRAPH_DENSITY_AMOUNT; densityIndex++) {
		// Dla kazdej ilosci wierzcholkow
		for (int vertexAmountIndex = 0; vertexAmountIndex < GRAPH_SIZE_AMOUNT; vertexAmountIndex++) {
			prevFileMatrix.open(getPrevFilePath(fileNameMatrix));
			newFileMatrix.open(getNewFilePath(fileNameMatrix));

			prevFileList.open(getPrevFilePath(fileNameList));
			newFileList.open(getNewFilePath(fileNameList));

			if (prevFileMatrix.is_open()) {
				isPrevFileOkMatrix = true;
			}

			if (prevFileList.is_open()) {
				isPrevFileOkList = true;
			}

			string currentLineMatrix = "";
			string currentLineList = "";

			getline(prevFileMatrix, currentLineMatrix);
			getline(prevFileList, currentLineList);

			// Wprowadzam nazwy kolumn do plikow
			newFileMatrix << currentLineMatrix <<
				"V" <<
				graphSizes[vertexAmountIndex] <<
				"|D" <<
				graphDensities[densityIndex] <<
				separator << endl;

			newFileList << currentLineList
				<< "V" <<
				graphSizes[vertexAmountIndex] <<
				"|D" <<
				graphDensities[densityIndex] <<
				separator << endl;

			// Przed rozpoczeciem proby
			cout << endl << "BellmanFord, density(" << graphDensities[densityIndex] << ")" <<
				", vertexAmount(" << graphSizes[vertexAmountIndex] << ")";

			// Ilosc powtorzen dla tych samych parametrow grafu
			for (int repetition = 0; repetition < testSize; repetition++) {
				// Przed rozpoczeciem pomiaru
				if (isPrevFileOkMatrix) {
					getline(prevFileMatrix, currentLineMatrix);
				}
				if (isPrevFileOkList) {
					getline(prevFileList, currentLineList);
				}

				resetBeforeMeasurement();
				deleteGraphs();

				matrixGraph = new MatrixGraph();
				listGraph = new ListGraph();

				// Generuje losowy graf (ten sam dla obu implementacji)
				matrixGraph->generateRandom(graphSizes[vertexAmountIndex], graphDensities[densityIndex], MST_TYPE, 1, 20);
				matrixGraph->saveToFile(tempFileName, MST_TYPE);
				listGraph->loadFromFile(tempFileName);
				remove(tempFileName.c_str());

				// A to takie kropki, zeby bylo widac jak pomiar postepuje w konsoli :)
				cout << '.';

				// Rozpoczynam pomiar dla macierzowej implementacji
				timeUtilsMatrix.start();
				{
					matrixGraph->bellmanFord();
				}
				// Koncze pomiar dla macierzowej implementacji
				timeUtilsMatrix.stop();

				// Rozpoczynam pomiar dla listowej implementacji
				timeUtilsList.start();
				{
					listGraph->bellmanFord();
				}
				// Koncze pomiar dla listowej implementacji
				timeUtilsList.stop();

				// Po zakonczeniu pomiaru
				delete resultMatrix;
				delete resultList;

				totalTimeMatrix = timeUtilsMatrix.getDuration();
				totalTimeList = timeUtilsList.getDuration();

				//cout << "Matrix duration" << timeUtilsMatrix.getDuration() << endl;
				//cout << "List duration" << timeUtilsList.getDuration() << endl;

				newFileMatrix << currentLineMatrix << totalTimeMatrix << separator << endl;
				newFileList << currentLineList << totalTimeList << separator << endl;
			}
			newFileMatrix.close();
			prevFileMatrix.close();
			newFileList.close();
			prevFileList.close();
			prevFileMatrix.clear();
			newFileMatrix.clear();
			prevFileList.clear();
			newFileList.clear();

			remove(getPrevFilePath(fileNameMatrix).c_str());
			if (rename(getNewFilePath(fileNameMatrix).c_str(), getPrevFilePath(fileNameMatrix).c_str()) != 0) {
				cout << "Couldn't rename the file." << endl;
			}
			remove(getPrevFilePath(fileNameList).c_str());
			if (rename(getNewFilePath(fileNameList).c_str(), getPrevFilePath(fileNameList).c_str()) != 0)
			{
				cout << "Couldn't rename the file." << endl;
			}
		}
	}

	deleteGraphs();

	rename(getPrevFilePath(fileNameMatrix).c_str(), getNewFilePath(fileNameMatrix).c_str());
	rename(getPrevFilePath(fileNameList).c_str(), getNewFilePath(fileNameList).c_str());
}

void MeasureUtil::resetBeforeMeasurement()
{
	totalTimeMatrix = 0;
	totalTimeList = 0;
}

void MeasureUtil::deleteGraphs()
{
	delete matrixGraph;
	delete listGraph;
	matrixGraph = nullptr;
	listGraph = nullptr;
}

string MeasureUtil::getPrevFilePath(string fileName)
{
	return resultDirectory + fileName + "_prev" + '.' + extension;
}

string MeasureUtil::getNewFilePath(string fileName)
{
	return resultDirectory + fileName + '.' + extension;
}
