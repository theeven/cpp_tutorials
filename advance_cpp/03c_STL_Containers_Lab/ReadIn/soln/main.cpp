#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

void readinNames( std::vector<std::string> &v, std::istream &is ) {
    int n;
    is >> n;
    std::istream_iterator<std::string> in( is ), end;
    v.reserve(n);
    std::copy( in, end, std::back_inserter(v) );
}

int main() {
	using namespace std;
	
	vector<std::string> names;

	cout << "Enter the number of strings, then that many strings, then EOF\n";
	cout << "(EOF is Control-Z under Windows, or ^D at the start of a line on Unix)\n";

	readinNames( names, std::cin );
	reverse_copy( names.begin(), names.end(), std::ostream_iterator<std::string>( std::cout, "\n" ) );
	
	return 0;
}
