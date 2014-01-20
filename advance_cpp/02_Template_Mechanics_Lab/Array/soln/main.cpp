#include <iostream>
#include "array.h"

int main() {
	using namespace std;
		
	Array<int,5> a1(123);
	Array<int,5> a2(321);
	std::cout << (a1 == a2) << std::endl;
	a1 = a2;
	std::cout << (a1 == a2) << std::endl;
		
	return 0;
}
