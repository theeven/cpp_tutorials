#include <iostream>
#include <string>
#include <list>

// First version of myFind.
//
template <typename T>
T *myFind( T *begin, T *end, bool (*pred)( const T & ) ) {
	for( T *i = begin; i != end; ++i )
		if( pred(*i) )
			return i;
	return end;
}

int a[] = { 3,1,4,1,5 };
const int alen = sizeof(a)/sizeof(a[0]);
bool isGreaterThan3( const int &a )
	{ return a > 3; }

std::string b[] = { "Jan", "Jen", "Joe", "Meg", "John", "Joan" };
const int blen = sizeof(b)/sizeof(b[0]);

// A predicate.
//
bool isLongerThan3( const std::string &a )
	{ return a.size() > 3; }

// Second, more flexible, version of myFind.
//
template <typename Iter, typename Pred>
Iter myFind2( Iter begin, Iter end, Pred pred ) {
	for( Iter i = begin; i != end; ++i )
		if( pred(*i) )
			return i;
	return end;
}

// Some more predicates.
//
int isMoreLengthyThan3( std::string a )
	{ return a.size() > 3; }

struct IsLongerThan3 {
	bool operator ()( const std::string &a ) const
		{ return isLongerThan3(a); }
};

int main() {
	using namespace std;
	
	// Testing first version.
	{
	int *result1 = myFind2( a, a+alen, isGreaterThan3 );
	if( result1 != a+alen )
		cout << "We found an int: " << *result1 << endl;
	string *result2 = myFind2( b, b+blen, isLongerThan3 );
	if( result2 != b+blen )
		cout << "We found a string: " << *result2 << endl;
	}
	
	// Testing second version, flexible predicates.
	{
	int *result1 = myFind( a, a+alen, isGreaterThan3 );
	if( result1 != a+alen )
		cout << "We found an int: " << *result1 << endl;
	string *result2 = myFind( b, b+blen, isLongerThan3 );
	if( result2 != b+blen )
		cout << "We found a string: " << *result2 << endl;
	string *result3 = myFind2( b, b+blen, isMoreLengthyThan3 );
	if( result3 != b+blen )
		cout << "We found a string: " << *result3 << endl;
	string *result4 = myFind2( b, b+blen, IsLongerThan3() );
	if( result4 != b+blen )
		cout << "We found a string: " << *result4 << endl;
	}
	
	// Testing second version, flexible range.
	{
	list<int> intlist(a, a+alen);
	list<int>::iterator result1 = myFind2( intlist.begin(), intlist.end(), isGreaterThan3 );
	if( result1 != intlist.end() )
		cout << "We found an int: " << *result1 << endl;
	}
	return 0;
}
