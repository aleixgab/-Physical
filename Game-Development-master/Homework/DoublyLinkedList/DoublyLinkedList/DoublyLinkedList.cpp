#include <iostream>
#include "DoublyLinkedList.h"
using namespace std;

int main() {
	List<int> a;

	a.pushBack(1);
	a.pushFront(3);
	a.insert(1, 10);

	a.print();

	cout << "The size of the List is: " << a.size() << endl;

	a.pushFront(5);
	a.pushFront(6);
	a.pushFront(7);
	a.pushFront(8);
	a.pushBack(9);

	a.print();

	a.popFront();
	a.popBack();

	a.print();

	cout << a.front() << endl;

	if (a.empty())
		cout << "The List is empty" << endl;
	else
		cout << "The List is not empty" << endl;

	cout << "Value in position 4: " << a.getValue(4) << endl;
	cout << "Value in position 50: " << a.getValue(50) << endl;

	a.remove(4);
	cout << "Removed value from position 4" << endl;

	a.print();

	a.insert(0, -100);
	a.insert(50, 100);

	a.print();

	a.clear();
	cout << "Cleared List" << endl;

	if (a.empty())
		cout << "The List is empty" << endl;
	else
		cout << "The List is not empty" << endl;




	system("pause");
	return 0;
}