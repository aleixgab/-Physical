#include <iostream>
using namespace std;

#include "DynamicArray.h"
#include "DoublyLinkedList.h"

void List::addData(DynArray& dynArray) const {
	if (first != nullptr) {
		node* iterator = first;
		int i = 0;
		bool yes = true;

		while (iterator != nullptr) {
			dynArray.insert(dynArray.size(), iterator->value);

			iterator = iterator->next;
		}
	}
}

void DynArray::addData(List& list) const {
	if (size() != 0) {

		for (int i = 0; i < numElems; i++) {
			list.pushBack(arrayElems[i]);
		}
	}
}

int main() {
	List l;
	DynArray d;

	d.insert(0, 3);

	l.pushFront(1);
	l.pushFront(2);
	l.pushFront(3);
	l.pushFront(10);
	l.pushFront(5);

	cout << "List data:" << endl;
	l.print();

	cout << "Linked List data to a Dynamic Array:" << endl;
	l.addData(d);
	d.print();

	cout << "Dynamic Array data to a Linked List:" << endl;
	d.addData(l);
	l.print();

	cout << endl;

	system("pause");
	return 0;
}