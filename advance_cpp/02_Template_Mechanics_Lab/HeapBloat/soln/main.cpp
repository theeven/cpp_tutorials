#include <iostream>
#include <iterator>
#include "heap.h"

template <typename T, typename Out>
void extractHeap( Heap<T> &h, Out dest ) {
    while( !h.empty() )
        *dest++ = h.pop();
}

int main() {
	// See implementation of Heap specialization in heap.h
	using namespace std;
	
	Heap<const char *> names;
	names.push( "Fred" );
	names.push( "Alice" );
	names.push( "Murgatroid" );
	names.push( "Eleazer" );
	extractHeap( names, ostream_iterator<const char *>(cout,"\n") );
	
	return 0;
}
