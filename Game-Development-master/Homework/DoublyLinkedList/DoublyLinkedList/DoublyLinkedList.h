#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

template <class Type>
class List {
public:
	List();
	~List();

	void pushFront(const Type& elem);
	void pushBack(const Type& elem);
	void popFront();
	void popBack();
	void insert(unsigned int pos, const Type& elem);
	void remove(unsigned int pos);

	Type front() const;
	Type back() const;

	Type getValue(unsigned int pos) const;

	bool empty() const;
	int size() const;
	void clear();

	void print() const;

private:
	struct node {
		Type value;
		node* next;
		node* previous;
	};
	node* first;
};

template <class Type>
List<Type>::List() {
	first = nullptr;
}

template <class Type>
List<Type>::~List() {
	clear();
}

template <class Type>
void List<Type>::pushFront(const Type& elem) {
	node* new_node = new node;
	new_node->value = elem;
	new_node->previous = nullptr;
	new_node->next = first;

	if (first != nullptr)
		first->previous = new_node;

	first = new_node;
}

template <class Type>
void List<Type>::pushBack(const Type& elem) {
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

template <class Type>
void List<Type>::popFront() {
	if (first != nullptr) {
		node* aux = first;
		
		first = first->next;

		if (first != nullptr) {
			first->previous = nullptr;
		}
		
		delete aux;
	}
}

template <class Type>
void List<Type>::popBack() {
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

template <class Type>
void List<Type>::insert(unsigned int pos, const Type& elem) {
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

template <class Type>
void List<Type>::remove(unsigned int pos) {

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

template <class Type>
Type List<Type>::front() const {
	if (first != nullptr) {
		return first->value;
	}
	else {
		cout << "List is empty" << endl;
		return 0;
	}
}

template <class Type>
Type List<Type>::back() const {
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

template <class Type>
Type List<Type>::getValue(unsigned int pos) const {
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

template <class Type>
bool List<Type>::empty() const {
	return first == nullptr;
}

template <class Type>
int List<Type>::size() const {
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

template <class Type>
void List<Type>::clear() {

	while (first != nullptr) {

		node* aux = first;

		first = first->next;

		delete aux;
	}

	first = nullptr;
}

template <class Type>
void List<Type>::print() const {

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