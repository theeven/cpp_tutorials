#include <iostream>
#include "heap_fptr.h"

void hello( const char *msg ) // a simple test function
	{ std::cout << "\nHello " << msg << '!' << std::endl; }

int main() {
	// See implementation in heap1_fptr.h
		
	Heap<void(*)(const char *)> funcs;
	funcs.push( hello );
	funcs.pop()("heap");
		
	return 0;
}
