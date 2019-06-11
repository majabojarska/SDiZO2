#pragma once
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cmath>

class DynamicArray
{
	int *dataArray; // Wskaznik na tablice typu int
	int size; // Obecna ilosc elementow w tablicy

public:
	DynamicArray();
	~DynamicArray();

	bool containsValue(int val);
	void insertAtFront(int value);
	void insertAtIndex(int index, int value);
	void insertAtBack(int value);
	void insert(int value);

	int getSize();
	int getAtIndex(int index);
	
	void deleteAtIndex(int index);
	void deleteAll();
	void deleteAtFront();
	void deleteAtBack();
	
	int getIndexOfValue(int value);
	void deleteByValue(int value);

	bool isEmpty();

	void generateRandom(int size, int maxValue = 1000);
	void display();

	void writeToStream(std::ostream& out, std::string separator = "\n");


	friend std::ostream& operator<< (std::ostream& out, DynamicArray* dynamicArray);
};

