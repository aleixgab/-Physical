#include <iostream>
#include "Vector3.h"
using namespace std;

int main() {
	Vec3<float> a(0, 2.9, -3), b(2.1, 5, -9.5);
	Vec3<float> d(2.1, 5, -9.5);

	cout << "a(" << a.x << ", " << a.y << ", " << a.z << ")" << endl;
	a.x = 4;
	cout << "Setting a.x to 4..." << endl;
	cout << "a.x = " << a.x << endl;

	Vec3<float> c = a + b;
	cout << "c(" << c.x << ", " << c.y << ", " << c.z << ")" << endl;

	if (a == c)
		cout << "a is equal to c" << endl;
	else
		cout << "a is not equal to c" << endl;

	if (d == b)
		cout << "d is equal to b" << endl;
	else
		cout << "d is not equal to b" << endl;

	cout << endl;

	Vec3<int> x(1, 2, -3), y(-2, 1, 5);

	cout << "Original vectors:" << endl;
	cout << "x(" << x.x << ", " << x.y << ", " << x.z << ")" << endl;
	cout << "y(" << y.x << ", " << y.y << ", " << y.z << ")" << endl;

	cout << endl;
	cout << "Setting x to zero..." << endl;
	x.set_to_zero();
	cout << "x(" << x.x << ", " << x.y << ", " << x.z << ")" << endl;
	if (x.is_zero())
		cout << "x is zero" << endl;
	else
		cout << "x is not zero" << endl;

	cout << endl;
	cout << "Setting x to its original values..." << endl;
	x.x = 1;
	x.y = 2;
	x.z = -3;

	cout << endl;
	x += y;
	cout << "x += y" << endl;
	cout << "x(" << x.x << ", " << x.y << ", " << x.z << ")" << endl;
	cout << "y(" << y.x << ", " << y.y << ", " << y.z << ")" << endl;

	cout << endl;
	x -= y;
	cout << "x -= y" << endl;
	cout << "x(" << x.x << ", " << x.y << ", " << x.z << ")" << endl;
	cout << "y(" << y.x << ", " << y.y << ", " << y.z << ")" << endl;

	cout << endl;
	cout << "Multiply y*k. Introduce your k: " << endl;
	int k = 1;
	cin >> k;

	Vec3<int> z;
	z = y * k;

	cout << "z(" << z.x << ", " << z.y << ", " << z.z << ")" << endl;

	cout << endl;
	int result = 0;
	result = x * y;
	cout << "Dot product:" << endl << "x * y = " << result << endl;

	Vec3<int> distance1(1, 1, 1), distance2(2, 2, 2);

	cout << "Distance between distance1 and distance2: " << distance1.distance(distance2) << endl;

	cout << endl;
	system("pause");
	return 0;
}

