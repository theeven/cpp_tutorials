#ifndef READDICTIONARY_H
#define READDICTIONARY_H

#include <iostream>
#include <algorithm>
#include <ctime>
#include <fstream>

template <template <typename,class> class Cont, typename T, class A>
void readDictionary( const char *dictionaryFile, Cont<T,A> &words ) {
	using namespace std;

	cout << "Reading dictionary..." << flush;
	ifstream fs( dictionaryFile );
	istream_iterator<T> i( fs );
	istream_iterator<T> end;
	std::copy( i, end, back_inserter( words ) );

	// only sort dictionary if unsorted
	if( adjacent_find( words.begin(), words.end(), greater<T>() ) != words.end() ) {
		cout << "sorting dictionary..." << flush;
		sort( words.begin(), words.end() );
	}

	cout << "done. (" << words.size() << " words)" << endl;
}

#endif
