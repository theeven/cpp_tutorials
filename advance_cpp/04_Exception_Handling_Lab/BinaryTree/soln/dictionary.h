#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

//
//	Copy a file of words to an output sequence.
//	The content will be truncated if length exceeds the
//	second argument.
//	The original input sequence will be randomized, sorted,
//	left alone based on the value of the third argument.
//
//	Example usage:
//		vector<string> vs;
//		getDictionary( back_inserter(vs), 5000, SORTED, "c:diction.txt" );

enum Orders { ASIS, SORTED, RANDOMIZED };

template <typename Out>
void getDictionary( Out out, std::size_t n = -1, Orders order = ASIS, const char *pathname = "c:diction.txt" ) {
	using namespace std;
	ifstream fs( pathname );
	istream_iterator<string> i( fs );
	istream_iterator<string> end;
	vector<string> temp( i, end );
	
	if( order == RANDOMIZED )
		random_shuffle( temp.begin(), temp.end() );
	else if( order == SORTED )
		// not fancy; we just sort by <
		sort( temp.begin(), temp.end() );
	if( n < temp.size() )
		temp.resize( n );
	copy( temp.begin(), temp.end(), out );
}

#endif
