#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <iterator>
#include <functional>
#include "crosswordcomp.h"

const std::string baseDirectory = "./";
const std::string inputDictionary = baseDirectory+"diction.txt";
const std::string outputDictionary = baseDirectory+"crossworddict.txt";

inline bool
myStrComp( const std::string &a, const std::string &b ) {
	if( a.length() < b.length() ) return true;
	if( a.length() > b.length() ) return false;
	return a < b;
}

struct MyStrComp : public std::binary_function<std::string,std::string,bool> {
	bool operator ()( const std::string &a, const std::string &b ) const
		{ return myStrComp( a, b ); }
};

template <class Cont>
void readDictionary( const std::string &dictionary, Cont &words ) {
	using namespace std;

	ifstream fs( dictionary.c_str() );
	istream_iterator<string> i( fs );
	istream_iterator<string> end;
	copy( i, end, back_inserter( words ) );
}

void makeCrosswordDictionary( const std::string &inputFile, const std::string &outputFile ) {
	using namespace std;
	
	vector<string> words;
	readDictionary( inputFile, words ); 
	sort( words.begin(), words.end(), MyStrComp() );
	ofstream f( outputFile.c_str() );
	ostream_iterator<string> out( f, "\n" );
	copy( words.begin(), words.end(), out );
}

int main() {
	makeCrosswordDictionary( inputDictionary, outputDictionary );
  
	return 0;
}
