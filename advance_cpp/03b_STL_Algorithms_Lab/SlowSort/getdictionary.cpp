#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "getdictionary.h"

std::vector<std::string> getDictionary( std::size_t n ) {
	using namespace std;
	
	cout << "\nReading, randomizing and sizing dictionary..." << flush;
	ifstream fs( dictionaryFile );
	istream_iterator<string> i( fs );
	istream_iterator<string> end;
	vector<string> words;
	std::copy( i, end, back_inserter( words ) );
	random_shuffle( words.begin(), words.end() );
	if( n >= 0 && n < words.size() )
		words.resize( n );
	cout << "done." << endl;
	return words;
}
