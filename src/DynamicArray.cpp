#include "DynamicArray.h"

void DynamicArray::deleteAtIndex(int index)
{
	if (index >= 0 && index < this->size) { // Kopiowanie istotnych komorek pamieci, z pominieciem elementu usuwanego
		size--;
		int* newArr = new int[size]; // Utworzenie tablicy o 1 mniejszej

		memcpy(newArr, dataArray, sizeof(int)*(index));
		memcpy(newArr + index, dataArray + index + 1, sizeof(int)*(this->size - index));

		delete[] dataArray; // Usuniecie tablicy "starej"
		dataArray = newArr; // Przypisanie wskaznika na nowa tablice
	}
	else { // Podano indeks poza tablica
		return;
	}
}

void DynamicArray::deleteAll() {
	delete[] this->dataArray;
	this->dataArray = new int[0];
	this->size = 0;
}

void DynamicArray::deleteAtFront()
{
	if (getSize() > 0) {
		deleteAtIndex(0);
	}
}

void DynamicArray::deleteAtBack()
{
	if (getSize() > 0) {
		deleteAtIndex(getSize() - 1);
	}
}

int DynamicArray::getIndexOfValue(int value)
{
	for (int i = 0; i < size; i++) {
		if (this->dataArray[i] == value) {
			return i;
		}
	}
	return -1;
}

void DynamicArray::deleteByValue(int value)
{
	deleteAtIndex(getIndexOfValue(value));
}

bool DynamicArray::isEmpty()
{
	return size == 0;
}

void DynamicArray::generateRandom(int size, int maxValue)
{
	
	this->size = size;
	int* newArr = new int[size]; // Utworzenie tablicy o podanym rozmiarze

	for (int i = 0; i < size; i++) {
		newArr[i] = rand() % maxValue;
	}

	delete[] dataArray; // Usuniecie tablicy "starej"
	dataArray = newArr; // Przypisanie wskaznika na nowa tablice
}

void DynamicArray::display()
{
	std::cout << this;
}

void DynamicArray::writeToStream(std::ostream& out, std::string separator)
{
	out << this->getSize() << separator;
	for (int i = 0; i < this->getSize(); i++) {
		out << this->getAtIndex(i) << separator;
	}
}

int DynamicArray::getSize()
{
	return this->size;
}

DynamicArray::DynamicArray()
{
	size = 0;
	dataArray = new int[0];
}

DynamicArray::~DynamicArray()
{
	delete[] dataArray;
}

bool DynamicArray::containsValue(int val)
{
	for (int i = 0; i < this->size; i++) {
		if (dataArray[i] == val) {
			return true;
		}
	}
	return false;
}
void DynamicArray::insertAtIndex(int index, int value)
{
	if (index < 0 || index > getSize()) {
		return;
	}
	size++;
	int* newArr = new int[size]; // Utworzenie tablicy o 1 wiêkszej

	if (index >= 0 && index <= this->size) { // Kopiowanie istotnych komorek pamieci
		memcpy(newArr, dataArray, sizeof(int)*(index));
		memcpy(newArr + index + 1, dataArray + index, sizeof(int)*(this->size - index - 1));
	}
	else { // Podano indeks poza tablica
		return;
	}
	newArr[index] = value;
	delete[] dataArray; // Usuniecie tablicy "starej"
	dataArray = newArr; // Przypisanie wskaznika na nowa tablice
}

void DynamicArray::insertAtFront(int value)
{
	insertAtIndex(0, value);
}

void DynamicArray::insertAtBack(int value)
{
	insertAtIndex(getSize(), value);
}

void DynamicArray::insert(int value)
{
	this->insertAtBack(value);
}

int DynamicArray::getAtIndex(int index)
{
	return dataArray[index];
}

std::ostream& operator<< (std::ostream& out, DynamicArray* dynamicArray) {
	if (dynamicArray->size > 0) {
		for (int i = 0; i < dynamicArray->size; i++) {
			out << dynamicArray->dataArray[i] << ' ';
		}
	}

	return out;
}
