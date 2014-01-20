#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <functional>
#include "readDictionary.h"

const char * const dictionaryFile = "C:\\content\\scd\\x_courses\\courses_semantics\\final_modules\\labs\\STL2_Algorithms\\Anagram\\soln\\diction.txt";

void exercise2() {
	using namespace std;

	vector<string> words;
	readDictionary( dictionaryFile, words );
	
	// Interactive portion.  (No checking of or recovery from
	// user input errors...)
	const int maxWordLen = 120; // max len reserved for input word from user
	const int maxPermLen = 10; // permute only words of length <= maxPermLen
	while( true ) {
		cout << "Enter a word (or '.' to end):  " << flush;
		char anagram[maxWordLen];
		cin >> anagram;
		if( strcmp( anagram, "." ) == 0 )
			break;
		cout << "Anagrams of " << anagram << ':' << endl;
		if( strlen( anagram ) > maxPermLen ) {
			cout << "Word is too long!" << endl;
			continue;
		}

		sort( anagram, anagram+strlen(anagram) );
		do
			if( binary_search( words.begin(), words.end(), anagram ) )
				cout << '\t' << anagram << endl;
		while( next_permutation( anagram, anagram+strlen(anagram) ) );
	}
}

int main() {
	exercise2();
	
	return 0;
}
