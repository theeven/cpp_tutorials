#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <list>
#include <cassert>
#include <vector>

int main() {
	using namespace std;
	
	const char *dictionaryFile = "C:\\content\\scd\\x_courses\\courses_semantics\\final_modules\\labs\\STL3_Containers\\CrossWord\\soln\\crossworddict.txt";
	const bool wordLengthStatisticsDesired = true;

	// Read in crossword dictionary.  Dictionary is sorted according
	// to 1) word length, and then 2) lexicographically.
	list<string> words;
	{
	cout << "Reading dictionary..." << flush;
	ifstream fs( dictionaryFile );
	istream_iterator<string> in( fs );
	istream_iterator<string> end;
	copy( in, end, back_inserter( words ) );
	cout << "done. (" << words.size() << " words)" << endl;
	}

	// Resplice the list of words into a vector of lists of
	// equal-length words.  Words on each list remain sorted
	// in lexicographic order.
	vector< list<string> > dict(1);
	int curwordlen = 0;
	for( list<string>::iterator i( words.begin() ); i != words.end(); ++i ) {
		if( i->length() > curwordlen ) {
			// prepare vector to hold next list of equal length words
			int newwordlen = i->length();
			for( int j = curwordlen; j < newwordlen; ++j )
				dict.push_back( list<string>() );
			assert( dict.size() == newwordlen+1 );

			// splice list of equal length words from head of list to end of vector
			dict[curwordlen].splice( dict[curwordlen].begin(), words, words.begin(), i );

			curwordlen = newwordlen;
		}
	}
	// all the longest words go at the end of the vector
	dict.back().splice( dict.back().begin(), words );

	if( wordLengthStatisticsDesired ) {
		cout << "\nWord Length Statistics" << endl;
		for( int len = 0; len < dict.size(); ++len )
			cout << len << ":\t" << dict[len].size() << endl;
	}
	
	// Interactive portion.  (No error checking or recovery for
	// user input...)
	while( true ) {
		cout << "\nEnter a word length, a letter, and a position (or '0' to end):  " << flush;
		int length; char letter; int position;
		cin >> length;
		if( length == 0 )
			break;
		cin >> letter >> position;
		if( length > dict.size()+1 ) {
			cout << "No words that long in dictionary!" << endl;
			continue;
		}
		if( position > length || position < 0 ) {
			cout << "Letter position outside of word!" << endl;
			continue;
		}

		for( list<string>::iterator i( dict[length].begin() );
			i != dict[length].end(); ++i )
			if( (*i)[position-1] == letter )
				cout << *i << endl;
		cout << endl << endl;
	}
	
	return 0;
}
