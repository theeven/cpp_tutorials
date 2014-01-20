#include <iostream>
#include <cstring>
#include <iterator>
#include <functional>
#include "heap2.h"

template <typename T, typename C, typename Out>
void extractHeap2( Heap2<T,C> &h, Out dest ) {
    while( !h.empty() )
        *dest++ = h.pop();
}

//	A comparitor for Heaps of const char *.
//	The 2-parameter Heap template is in heap2.h
inline bool strLess( const char *a, const char * b )
    { return std::strcmp( a, b ) < 0; }

// Note:  The use of binary_function is for STL conformance.  If you're not familiar
// with STL conventions, you can safely ignore it (until you start using the STL).
struct StrLess : public std::binary_function<const char *, const char *, bool> {
	bool operator ()( const char *a, const char *b ) const
		{ return strLess( a, b ); }
};

//	A comparitor for Heaps of pointers.
//	The 2-parameter Heap template is in heap2.h
template <typename T>
struct PtrLess : public std::binary_function<const T *, const T *, bool> {
	bool operator ()( const T *a, const T *b ) const
		{ return *a < *b; }
};

int main() {
	using namespace std;	
	// Using a function object rather than a complete specialization
	// for const char *.
	Heap2<const char *,StrLess> names1;
	names1.push( "Fred" );
	names1.push( "Alice" );
	names1.push( "Murgatroid" );
	names1.push( "Eleazer" );
	cout << "\nNames ordered by function object:" << endl;
	extractHeap2( names1, ostream_iterator<const char *>(cout,"\n") );
	
	// Using a function pointer instead of a complete specializaton
	// for const char *.
	// Question: What would happen if we didn't pass strLess to the ctor?
	// Question: Which do you think executes faster, the function object version or
	// this version with the function pointer?
	Heap2<const char *,bool (*)(const char *, const char *)> names2( strLess );
	names2.push( "Fred" );
	names2.push( "Alice" );
	names2.push( "Murgatroid" );
	names2.push( "Eleazer" );
	cout << "\nNames ordered by function pointer:" << endl;
	extractHeap2( names2, ostream_iterator<const char *>(cout,"\n") );
	
	// Using a function object rather than a partial specialization
	// for T *.
	Heap2<double *,PtrLess<double> > doubles;
	doubles.push( new double(1.1) );
	doubles.push( new double(4.4) );
	doubles.push( new double(3.3) );
	doubles.push( new double(2.2) );
	cout << "\nDouble pointers ordered by function object:" << endl;
	vector<double *> d;
	extractHeap2( doubles, back_inserter(d) );
	for( vector<double *>::iterator i(d.begin()); i != d.end(); ++i ) {
		cout << **i << endl;
		delete *i;
	}
	
	return 0;
}
