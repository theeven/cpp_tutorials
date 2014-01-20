#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>

template <typename T>
void merge( std::list<T> &l1, std::list<T> &l2, std::vector<T> &r ) {
    while( !l1.empty() && !l2.empty() ) {
        if( l1.front() < l2.front() ) {
            r.push_back( l1.front() );
            l1.pop_front();
        }
        else {
            r.push_back( l2.front() );
            l2.pop_front();
        }
    }
    while( !l1.empty() ) {
        r.push_back( l1.front() );
        l1.pop_front();
    }
    while( !l2.empty() ) {
        r.push_back( l2.front() );
        l2.pop_front();
    }
}

std::string a[] = { "Ann", "Barbara", "Constance", "Dorothy", "Edwina", "Zoe" };
const int alen = sizeof(a)/sizeof(a[0]);
std::string b[] = { "Art", "Bob", "Carl", "Dave", "Edward" };
const int blen = sizeof(b)/sizeof(b[0]);

int main() {
	std::cout << "Using our merge:" << std::endl;
	std::list<std::string> la( a, a+alen );
	std::list<std::string> lb( b, b+blen );
	std::vector<std::string> v;
	merge( la, lb, v );
	std::copy( v.begin(), v.end(), std::ostream_iterator<std::string>(std::cout, "!\n") );
	
	std::cout << "\nUsing std::merge:" << std::endl;
	la.assign( a, a+alen );
	lb.assign( b, b+blen );
	v.clear();
	std::merge( la.begin(), la.end(), lb.begin(), lb.end(), back_inserter(v) );
	std::copy( v.begin(), v.end(), std::ostream_iterator<std::string>(std::cout, "!\n") );
	
	return 0;
}

