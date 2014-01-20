#include <cstring>
#include <algorithm>
#include <functional>
#include <deque>
#include <iostream>
#include <iterator>

inline bool
crosswordComp( const char *a, const char *b ) {
	using namespace std;
	
    if( strlen( a ) < strlen( b ) ) return true;
    if( strlen( a ) > strlen( b ) ) return false;
    return strcmp( a, b ) < 0;
}

struct CrosswordComp : public std::binary_function<const char *,const char *,bool> {
    bool operator ()( const char *a, const char *b ) const
        { return crosswordComp( a, b ); }
};

template <typename T, std::size_t n>
std::size_t length( T (&)[n] ) { return n; }

int main() {
	using namespace std;
	
	const char *names[] = {
		"Annie", "Zarathustra", "Megan", "Constance", "Penelope", "August", "Zoe", "Aalfred" };
	deque<const char *> d( names, names+length(names) );
	sort( d.begin(), d.end(), CrosswordComp() );
	copy( d.begin(), d.end(), ostream_iterator<const char *>(cout,"\n") );
	
	return 0;
}
