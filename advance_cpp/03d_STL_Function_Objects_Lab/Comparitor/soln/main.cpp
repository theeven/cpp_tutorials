#include <iostream>
#include <deque>
#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <fstream>
#include "timer.h"
#include "slowsort.h"

template <class For>
void print( std::string label, For b, For e ) {
	std::cout << label << ":\t";
	while( b != e )
		std::cout << *b++;
	std::cout << std::endl;
}

template <class Cont>
void readDictionary( const std::string &dictionary, Cont &words ) {
	using namespace std;

	ifstream fs( dictionary.c_str() );
	istream_iterator<string> i( fs );
	istream_iterator<string> end;
	copy( i, end, back_inserter( words ) );
}

int main() {
	// See slowsort.h
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

	cout << "\nSlowsorting various containers..." << endl;
	cout << "\nVector\n";
	print( "before", v.begin(), v.end() );
	slowsort( v.begin(), v.end() );
	print( "after", v.begin(), v.end() );

	cout << "\nList\n";
	print( "before", l.begin(), l.end() );
	slowsort( l.begin(), l.end() );
	print( "after", l.begin(), l.end() );

	cout << "\nDeque\n";
	print( "before", d.begin(), d.end() );
	slowsort( d.begin(), d.end() );
	print( "after", d.begin(), d.end() );

	cout << "\nArray\n";
	print( "before", a, a+10 );
	slowsort( a, a+10 );
	print( "after", a, a+10 );
	
	cout << "\nSlowsorting various containers using a comparitor..." << endl;
	cout << "\nVector\n";
	print( "before", v.begin(), v.end() );
	slowsort( v.begin(), v.end(), greater<int>() );
	print( "after", v.begin(), v.end() );

	cout << "\nList\n";
	print( "before", l.begin(), l.end() );
	slowsort( l.begin(), l.end(), greater<int>() );
	print( "after", l.begin(), l.end() );

	cout << "\nDeque\n";
	print( "before", d.begin(), d.end() );
	slowsort( d.begin(), d.end(), greater<int>() );
	print( "after", d.begin(), d.end() );

	cout << "\nArray\n";
	print( "before", a, a+10 );
	slowsort( a, a+10, greater<int>() );
	print( "after", a, a+10 );

	cout << "\n\n***  TIMING TEST  ***" << endl;
	const string baseDirectory = "./";
	const string inputDictionary = baseDirectory+"diction.txt";
	vector<string> words;
	readDictionary( inputDictionary, words );
	{
		random_shuffle( words.begin(), words.end() );
		cout << "Sorting with STL sort..." << flush;
		Timer t;
		std::sort( words.begin(), words.end(), greater<string>() );
		cout << "done. (" << words.size() << " words, " << t << " seconds)" << endl;
	}
	{
		random_shuffle( words.begin(), words.end() );
		cout << "Sorting with slow_sort..." << flush;
		Timer t;
		slowsort( words.begin(), words.end(), greater<string>() );
		cout << "done. (" << words.size() << " words, " << t << " seconds)" << endl;
	}
    
	return 0;
}
