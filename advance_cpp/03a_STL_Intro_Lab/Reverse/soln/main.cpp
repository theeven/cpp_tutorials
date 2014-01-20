#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <list>

template <class C1, class C2 >
void reverse( const C1 &in, C2 &out ) {
    typedef typename C1::const_iterator I;
    if( !in.empty() ) {
        I i( in.end() );
        do
            out.push_back( *--i );
        while( i != in.begin() );
    }
}

template <class Cont>
void print( const char *title, const Cont &c, const char *separator = " ", std::ostream &os = std::cout ) {
	os << title;
	std::ostream_iterator<typename Cont::value_type> i(os,separator);
	std::copy( c.begin(), c.end(), i );
	os << std::endl;
}

int a[] = { 1,2,3,4,5,6,7,8,9 };
const int alen = sizeof(a)/sizeof(a[0]);

int main() {
	using namespace std;
	
	cout << "Using our reverse:" << endl;
	vector<int> src(a,a+alen);
	list<int> dest;
	print( "vector before:\t", src );
	print( "list before:\t", dest );
	reverse( src, dest );
	print( "vector after:\t", src );
	print( "list after:\t", dest );
	
	cout << "\nUsing std::reverse:" << endl;
	dest.clear(); // not necessary; just creating same initial condition as before...
	print( "vector before:\t", src );
	print( "list before:\t", dest );
	dest.assign( src.begin(), src.end() );
	std::reverse( dest.begin(), dest.end() );
	print( "vector after:\t", src );
	print( "list after:\t", dest );
	
	cout << "\nUsing std::reverse_copy:" << endl;
	dest.clear(); // creating same initial condition as before...
	print( "vector before:\t", src );
	print( "list before:\t", dest );
	std::reverse_copy( src.begin(), src.end(), back_inserter(dest) );
	print( "vector after:\t", src );
	print( "list after:\t", dest );
	
	return 0;
}
