#include <iostream>
#include <vector>
#include <deque>
#include <deque>
#include <list>
#include <string>
#include <algorithm>
#include "slowsort.h"
#include "timer.h"
#include "getdictionary.h"

template <class For>
void print( For b, For e ) {
	while( b != e )
		std::cout << *b++;
	std::cout << std::endl;
}

int main() {
	// See file slowsort.h
	using namespace std;
	
	int a[] = { 9, 3, 5, 2, 1, 4, 7, 0, 6, 8 };

	vector<int> v;
	list<int> l;
	deque<int> d;

	for( int i = 0; i < 10; ++i ) {
		v.push_back( a[i] );
		l.push_back( a[i] );
		d.push_back( a[i] );
	}

	cout << "Slowsorting various containers...\n" << endl;
	cout << "\nVector:\n";
	print( v.begin(), v.end() );
	slow_sort( v.begin(), v.end() );
	print( v.begin(), v.end() );

	cout << "\nList:\n";
	print( l.begin(), l.end() );
	slow_sort( l.begin(), l.end() );
	print( l.begin(), l.end() );

	cout << "\nDeque:\n";
	print( d.begin(), d.end() );
	slow_sort( d.begin(), d.end() );
	print( d.begin(), d.end() );

	cout << "\nArray:\n";
	print( a, a+10 );
	slow_sort( a, a+10 );
	print( a, a+10 );

	cout << "\n\n***  TIMING TEST  ***" << endl;
	const int SIZE = 10000;
	{
		vector<string> words( getDictionary(SIZE) );
		cout << "Sorting with STL sort..." << flush;
		Timer t;
		std::sort( words.begin(), words.end() );
		cout << "done. (" << words.size() << " words, " << t << " seconds)" << endl;
	}
	{
		vector<string> words( getDictionary(SIZE) );
		cout << "Sorting with slow_sort..." << flush;
		Timer t;
		slow_sort( words.begin(), words.end() );
		cout << "done. (" << words.size() << " words, " << t << " seconds)" << endl;
	}
	{
		vector<string> words( getDictionary(SIZE) );
		cout << "Sorting with bubble_sort..." << flush;
		Timer t;
		bubble_sort( words.begin(), words.end() );
		cout << "done. (" << words.size() << " words, " << t << " seconds)" << endl;
	}
	
	return 0;
}
