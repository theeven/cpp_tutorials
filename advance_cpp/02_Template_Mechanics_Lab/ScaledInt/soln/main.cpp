#include <iostream>
#include "scaledint.h"

int main() {
	using namespace std;
	
	{
	typedef ScaledInteger SI;
	cout << "Non-template:" << endl;
	SI i( 1 ), j( 3 ), k( 5 );
	
	cout << "i = " << i << " j = " << j << " k = " << k << endl;
	cout << "i + j = " << i+j << endl;
	cout << "i / j = " << i/j << endl;
	cout << "i * j = " << i*j << endl;
	cout << "i * j * k = " << i*j*k << endl;
	cout << "i + j * k = " << i+j*k << endl;
	cout << "(i + j) * k = " << (i+j)*k << endl;
	cout << "((i /= j) + k) = " << ((i /= j) + k) << endl;
	}
	
	{
	const int precision = 2;
	typedef short Base;

	typedef ScaledInt<precision,Base> SI;
	cout << "\nTemplate: Precision is " << precision << ", underlying type is " << typeid(SI::IntegerType).name() << endl;
	SI i( 1 ), j( 3 ), k( 5 );
	
	cout << "i = " << i << " j = " << j << " k = " << k << endl;
	cout << "i + j = " << i+j << endl;
	cout << "i / j = " << i/j << endl;
	cout << "i * j = " << i*j << endl;
	cout << "i * j * k = " << i*j*k << endl;
	cout << "i + j * k = " << i+j*k << endl;
	cout << "(i + j) * k = " << (i+j)*k << endl;
	cout << "((i /= j) + k) = " << ((i /= j) + k) << endl;
	}
	
	return 0;
}
