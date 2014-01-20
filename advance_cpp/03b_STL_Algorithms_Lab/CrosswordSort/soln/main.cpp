#include <string>
#include <functional>
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>

inline bool crosswordComp( const std::string &a, const std::string &b ) {
    if( a.size() < b.size() ) return true;
    if( a.size() > b.size() ) return false;
    return a < b;
}

struct CrosswordComp : public std::binary_function<std::string,std::string,bool> {
    bool operator ()( const std::string &a, const std::string &b ) const
        { return crosswordComp( a, b ); }
};

int main() {
	using namespace std;
	
	istream_iterator<string> in( cin );
	istream_iterator<string> end;
	vector<string> words( in, end );
	sort( words.begin(), words.end(), CrosswordComp() );
	copy( words.begin(), words.end(), ostream_iterator<string>(cout,"\n") );
	
	return 0;
}
