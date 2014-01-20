#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include "copy.h"

int main() {
	using namespace std;
	
	istream_iterator<string> in( cin ), end;
	ostream_iterator<string> out( cout, "\n" );
	vector<string> names;
	
	myCopy( in, end, back_inserter(names) );
	sort( names.begin(), names.end() );
	names.erase( unique( names.begin(), names.end() ), names.end() );
	myCopy( names.begin(), names.end(), out );
	
	return 0;
}
