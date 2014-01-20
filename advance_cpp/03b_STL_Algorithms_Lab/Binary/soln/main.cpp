#include <iostream>
#include <iterator>
#include "assocvec.h"

template <class Cont>
void print( const char *title, Cont &c, const char *separator = " ", std::ostream &os = std::cout ) {
	os << title;
	std::ostream_iterator<typename Cont::value_type> i(os,separator);
	std::copy( c.begin(), c.end(), i );
	os << std::endl;
}

int main() {
	using namespace std;
	
	int a[] = { 2, 1, 4, 4, 4, 5, 2 };
	const int alen = sizeof(a)/sizeof(a[0]);
	AssocVec<int> av( a, a+alen );
	print( "Before insertions: ", av );
	if( av.insert(2).second )
		cout << "inserted 2!" << endl;
	else
		cout << "2 already there." << endl;
	AssocVec<int>::iterator i = av.find(2);
	if( i != av.end() )
		cout << "found " << *i << endl;
	else
		cout << "can't find 2!" << endl;
	if( av.insert(7).second )
		cout << "inserted 7." << endl;
	else
		cout << "7 already there!" << endl;
	if( (i = av.find(7)) != av.end() )
		cout << "found " << *i << endl;
	else
		cout << "can't find 7!" << endl;
	if( av.insert(3).second )
		cout << "inserted 3." << endl;
	else
		cout << "3 already there!" << endl;
	if( (i = av.find(3)) != av.end() )
		cout << "found " << *i << endl;
	else
		cout << "can't find 3!" << endl;
	if( av.insert(0).second )
		cout << "inserted 0." << endl;
	else
		cout << "0 already there!" << endl;
	if( (i = av.find(0)) != av.end() )
		cout << "found " << *i << endl;
	else
		cout << "can't find 0!" << endl;
	print( "After insertions: ", av );
	
	return 0;
}
