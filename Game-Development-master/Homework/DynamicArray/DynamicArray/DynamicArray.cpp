#include <iostream>
using namespace std;
#include "DynamicArray.h"

int main() {
	DynArray<int> one;
	DynArray<int> two(3);

	two.insert(2, 3);
	two.insert(0, 1);
	two.insert(1, 2);
	two.insert(2, 3);
	two.insert(3, 4);
	two.insert(4, 5);
	two.print();

	two.insert(2, 9);
	two.print();

	two.insert(0, 100);
	two.insert(1, 40);
	two.print();

	if (one.empty())
		cout << "Array one is empty" << endl;
	else
		cout << "Array one is not empty" << endl;

	if (two.empty())
		cout << "Array two is empty" << endl;
	else
		cout << "Array two is not empty" << endl;

	cout << "two[0]=" << two[0] << endl;

	two.remove(0);
	two.print();
	two.remove(600);
	two.print();

	system("pause");
	return 0;
}