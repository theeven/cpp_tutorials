#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

int main() {
	using namespace std;
	
	vector<string> names;
	copy( istream_iterator<string>(cin), istream_iterator<string>(), back_inserter(names) );
	sort( names.begin(), names.end() );
	unique_copy( names.begin(), names.end(), ostream_iterator<string>(cout,"\n") );
	
	return 0;
}
