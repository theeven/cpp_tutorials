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
	
	int a[] = { 2, 1, 3, 4, 4, 4, 5, 3, 2 };
	AssocVec<int> av( a, a+9 );
	print( "Before insertions: ", av );
	if( av.insert(2) )
		cout << "inserted 2" << endl;
	else
		cout << "2 already there!" << endl;
	AssocVec<int>::iterator i = av.find(2);
	if( i != av.end() )
		cout << "found " << *i << endl;
	else
		cout << "can't find 2!" << endl;
	if( av.insert(7) )
		cout << "inserted 7" << endl;
	else
		cout << "7 already there!" << endl;
	if( (i = av.find(7)) != av.end() )
		cout << "found " << *i << endl;
	else
		cout << "can't find 7!" << endl;
	print( "After insertions: ", av );
	
	return 0;
}
