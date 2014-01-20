#include <list>
#include <iostream>
#include <iterator>

template <class T>
void stringLists( std::list< std::list<T> > &in, std::list<T> &r ) {
    for( typename std::list< std::list<T> >::iterator i( in.begin() ); i != in.end(); ++i )
        r.splice( r.end(), *i );
    in.clear();
}

int main() {
	using namespace std;
	
	int a[] = { 1,2,3,4 };
	const int alen = sizeof(a)/sizeof(a[0]);
	
	list<int> l1( a, a+alen );
	list<int> l2( a, a+alen );
	list<int> l3( a, a+alen );
	list< list<int> > ll;
	ll.push_back( l1 );
	ll.push_back( l2 );
	ll.push_back( l3 );
	
	list<int> lout;

	stringLists( ll, lout );
	copy( lout.begin(), lout.end(), ostream_iterator<int>(cout,"\n") );
	
	return 0;
}
