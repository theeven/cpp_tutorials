#include <iostream>
#include "stab.h"

int main() {
	Stab t;
	t.insert( "Joe", 10 );
	t.insert( "Mary", 12 );
	t.insert( "Alphonse", 14 );
	
	const Info *i( t.lookup("Mary") );
	std::cout << "Mary: " << i->value << std::endl;
	
	return 0;
}
