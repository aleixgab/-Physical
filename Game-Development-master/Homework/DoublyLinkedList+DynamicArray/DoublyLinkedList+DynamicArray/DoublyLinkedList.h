#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "DynamicArray.h"

class DynArray;

class List {
	friend class DynArray;

public:
	List();
	~List();

	void pushFront(const int& elem);
	void pushBack(const int& elem);
	void popFront();
	void popBack();
	void insert(unsigned int pos, const int& elem);
	void remove(unsigned int pos);

	int front() const;
	int back() const;

	int getValue(unsigned int pos) const;

	bool empty() const;
	int size() const;
	void clear();

	void print() const;

	//Add data to a Dynamic Array
	void addData(DynArray& dynArray) const;

private:
	struct node {
		int value;
		node* next;
		node* previous;
	};
	node* first;
};

List::List() {
	first = nullptr;
}

List::~List() {
	clear();
}

void List::pushFront(const int& elem) {
	node* new_node = new node;
	new_node->value = elem;
	new_node->previous = nullptr;
	new_node->next = first;

	if (first != nullptr)
		first->previous = new_node;

	first = new_node;
}

void List::pushBack(const int& elem) {
	node* new_node = new node;
	new_node->value = elem;
	new_node->next = nullptr;

	if (first != nullptr) { //1 or more elements in the List
		if (first->next != nullptr) { //More than 1 element in the List
			node* iterator = first;

			while (iterator->next != nullptr) {
				iterator = iterator->next;
			}

			new_node->previous = iterator;
			iterator->next = new_node;
		}
		else { //1 element in the List
			new_node->previous = first;
			first->next = new_node;
		}
	}
	else { //List is empty
		new_node->previous = nullptr;
		first = new_node;
	}
}

void List::popFront() {
	if (first != nullptr) {
		node* aux = first;

		first = first->next;

		if (first != nullptr) {
			first->previous = nullptr;
		}

		delete aux;
	}
}

void List::popBack() {
	if (first != nullptr) {
		if (first->next != nullptr) {
			node* iterator = first;

			while (iterator->next != nullptr) {
				iterator = iterator->next;
			}

			node* aux = iterator;

			iterator->previous->next = nullptr;

			delete aux;
		}
		else {
			node* aux = first;

			delete aux;
			first = nullptr;
		}
	}
}

void List::insert(unsigned int pos, const int& elem) {
	node* new_node = new node;
	new_node->value = elem;

	if (first != nullptr) {
		if (pos < size() && pos >= 0) {

			node* iterator = first;
			int i = 0;

			while (iterator->next != nullptr && i < pos) {
				iterator = iterator->next;
				i++;
			}

			node* aux = iterator->previous;

			new_node->previous = aux;
			new_node->next = iterator;

			if (aux != nullptr)
				aux->next = new_node;
			else
				first = new_node;

			iterator->previous = new_node;
		}
		else if (pos >= size()) {
			pushBack(elem);
		}
	}
	else {
		new_node->next = nullptr;
		new_node->previous = nullptr;
		first = new_node;
	}
}

void List::remove(unsigned int pos) {

	if (first != nullptr && pos < size() && pos >= 0) {

		node* iterator = first;
		int i = 0;

		while (iterator->next != nullptr && i < pos) {
			iterator = iterator->next;
			i++;
		}

		node* to_delete = iterator;

		if (iterator->next != nullptr) {
			iterator->next->previous = iterator->previous;
		}

		if (iterator->previous != nullptr) {
			iterator->previous->next = iterator->next;
		}
		else {
			first = iterator->next;
		}

		delete to_delete;
	}
}

int List::front() const {
	if (first != nullptr) {
		return first->value;
	}
	else {
		cout << "List is empty" << endl;
		return 0;
	}
}

int List::back() const {
	if (first != nullptr) {
		node* iterator = first;

		while (iterator->next != nullptr) {
			iterator = iterator->next;
		}

		return iterator->value;
	}
	else {
		cout << "List is empty" << endl;
		return 0;
	}
}

int List::getValue(unsigned int pos) const {
	if (first != nullptr && pos < size() && pos >= 0) {

		node* iterator = first;
		int i = 0;

		while (iterator->next != nullptr && i < pos) {
			iterator = iterator->next;
			i++;
		}

		return iterator->value;
	}
	else {
		cout << "Could not return any value" << endl;
		return 0;
	}
}

bool List::empty() const {
	return first == nullptr;
}

int List::size() const {
	int i = 0;

	if (first != nullptr) {

		i++;
		node* iterator = first;

		while (iterator->next != nullptr) {
			iterator = iterator->next;
			i++;
		}
	}

	return i;
}

void List::clear() {

	while (first != nullptr) {

		node* aux = first;

		first = first->next;

		delete aux;
	}

	first = nullptr;
}

void List::print() const {

	if (first != nullptr) {

		node* iterator = first;

		while (iterator != nullptr) {
			cout << iterator->value << "|";
			iterator = iterator->next;
		}

		cout << endl;
	}
}

#endif