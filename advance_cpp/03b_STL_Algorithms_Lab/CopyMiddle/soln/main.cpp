#include <iostream>
#include <algorithm>
#include <string>
#include <iterator>
#include <vector>

int main() {
	using namespace std;
	
	vector<string> names;
	copy( istream_iterator<string>(cin), istream_iterator<string>(), back_inserter(names) );
	int n = names.size();
	vector<string>::iterator b( names.begin() ), b13( b+n/3 ), b23( b+2*n/3 ), e( names.end() );
	nth_element( b, b23, e );
	nth_element( b, b13, b23 );
	copy( b13, b23, ostream_iterator<string>(cout,"\n" ) );
	
	return 0;
}
