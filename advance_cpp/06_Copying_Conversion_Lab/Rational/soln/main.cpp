#include <iostream>
#include "rational.h"

int main() {
	// See rational.h
	using namespace std;
	
	Rational a(1,2), b(3,4), c;
	cout << a << '*' << b << "==" << (c = a*b) << endl;
	cout << "Enter a rational number of the form a/b: " << flush;
	cin >> c;
	cout << "That was a " << c << " which is about " << c.toDouble() << endl;
		
	return 0;
}
