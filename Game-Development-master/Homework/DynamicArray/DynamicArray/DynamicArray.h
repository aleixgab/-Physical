#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#define MIN_ARRAY_BLOCK_SIZE 10

#include <iostream>
#include <assert.h>

template <class Type>
class DynArray {
public:
	DynArray();
	DynArray(unsigned int memSize);
	~DynArray();

	bool empty() const;
	unsigned int size() const;

	bool insert(unsigned int index, const Type& elem);
	bool remove(unsigned int index);

	Type& operator[] (unsigned int index) const;

	void print() const;

private:
	void allocMem(unsigned int memSize);
	void shrinkToFit();

	Type* arrayElems;
	unsigned int memSize;
	unsigned int numElems;
};

template <class Type>
DynArray<Type>::DynArray() {
	memSize = MIN_ARRAY_BLOCK_SIZE;
	numElems = 0;
	allocMem(memSize);
}

template <class Type>
DynArray<Type>::DynArray(unsigned int memSize) {
	this->memSize = memSize;
	numElems = 0;
	allocMem(this->memSize);
}

template <class Type>
DynArray<Type>::~DynArray() {
	if (arrayElems != nullptr)
		delete[] arrayElems;
	arrayElems = nullptr;
}

template <class Type>
bool DynArray<Type>::empty() const {
	return numElems == 0;
}

template <class Type>
unsigned int DynArray<Type>::size() const {
	return numElems;
}

template <class Type>
bool DynArray<Type>::insert(unsigned int index, const Type& elem) {
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

template <class Type>
bool DynArray<Type>::remove(unsigned int index) {
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

template <class Type>
Type& DynArray<Type>::operator[] (unsigned int index) const {
	assert(index < numElems);
	return arrayElems[index];
}

template <class Type>
void DynArray<Type>::shrinkToFit() {
	if (numElems == memSize)
		allocMem(numElems + MIN_ARRAY_BLOCK_SIZE);
}

template <class Type>
void DynArray<Type>::print() const {
	if (numElems != 0) {
		for (int i = 0; i < size(); ++i) {
			cout << arrayElems[i] << " - ";
		}
		cout << endl;
	}
	else {
		cout << "The array is empty" << endl;
	}
}

template <class Type>
//private function
void DynArray<Type>::allocMem(unsigned int memSize) {
	Type* aux = arrayElems;
	arrayElems = new Type[memSize];

	if (aux != nullptr) {
		for (int i = 0; i < numElems; ++i) {
			arrayElems[i] = aux[i];
		}
	}

	delete[] aux;
}

#endif