#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#define MIN_ARRAY_BLOCK_SIZE 10

#include <iostream>
#include <assert.h>
#include "DoublyLinkedList.h"

class List;

class DynArray {
	friend class List;

public:
	DynArray();
	DynArray(unsigned int memSize);
	~DynArray();

	bool empty() const;
	unsigned int size() const;

	bool insert(unsigned int index, const int& elem);
	bool remove(unsigned int index);

	int& operator[] (unsigned int index) const;

	void print() const;

	//Add data to a Linked List
	void addData(List& list) const;

private:
	void allocMem(unsigned int memSize);
	void shrinkToFit();

	int* arrayElems;
	unsigned int memSize;
	unsigned int numElems;
};

DynArray::DynArray() {
	memSize = MIN_ARRAY_BLOCK_SIZE;
	numElems = 0;
	allocMem(memSize);
}

DynArray::DynArray(unsigned int memSize) {
	this->memSize = memSize;
	numElems = 0;
	allocMem(this->memSize);
}

DynArray::~DynArray() {
	if (arrayElems != nullptr) {
		delete[] arrayElems;
		arrayElems = nullptr;
	}
}

bool DynArray::empty() const {
	return numElems == 0;
}


unsigned int DynArray::size() const {
	return numElems;
}

bool DynArray::insert(unsigned int index, const int& elem) {
	/*Cosas a tener en cuenta:
	-Posición del index.
	-Si hay o no algo en esa posición.
	-El index tiene que ser <= al numElems del array.
	-Al shiftearse todos los elementos hacia la derecha, ¿caben dentro del array o alguno se sale?
	-Cuando el array queda lleno y queremos añadir un nuevo elemento, ampliamos el array.
	*/

	if (index >= 0 && index <= numElems) {

		if (index == numElems - 1) { //Último elemento del array

			if (numElems == memSize) { //Array lleno
				shrinkToFit();

				arrayElems[numElems] = arrayElems[index];
			}

			arrayElems[index] = elem;
			numElems++;
			return true;
		}
		else if (index == numElems) { //Un elemento adelante del último

			if (numElems == memSize) { //Array lleno
				shrinkToFit();
			}

			arrayElems[index] = elem;
			numElems++;
			return true;
		}
		else { //Cualquier otra posición del array
			for (int i = numElems; i > index; --i) {
				if (numElems == memSize) {
					shrinkToFit();
				}

				arrayElems[i] = arrayElems[i - 1];
			}

			arrayElems[index] = elem;
			numElems++;
		}
	}
	else {
		return false;
	}

}

bool DynArray::remove(unsigned int index) {
	if (index >= 0 && index <= numElems) {

		for (int i = index; i < numElems; ++i) {
			arrayElems[i] = arrayElems[i + 1];
		}
		numElems--;
		return true;
	}
	else {
		return false;
	}
}

int& DynArray::operator[] (unsigned int index) const {
	assert(index < numElems);
	return arrayElems[index];
}

void DynArray::shrinkToFit() {
	if (numElems == memSize)
		allocMem(numElems + MIN_ARRAY_BLOCK_SIZE);
}

void DynArray::print() const {
	if (numElems != 0) {
		for (int i = 0; i < size(); ++i) {
			cout << arrayElems[i] << "|";
		}
		cout << endl;
	}
	else {
		cout << "The array is empty" << endl;
	}
}

//private function
void DynArray::allocMem(unsigned int memSize) {
	int* aux = arrayElems;
	arrayElems = new int[memSize];

	if (aux != nullptr) {
		for (int i = 0; i < numElems; ++i) {
			arrayElems[i] = aux[i];
		}
	}

	delete[] aux;
}

#endif