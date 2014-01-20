#include <iterator>
#include <functional>
#include <string>
#include <iostream>
#include <algorithm>

inline bool firstIsAorZ( const std::string &s )
    { return s[0]=='A' || s[0]=='Z'; }

struct FirstIsAorZ : public std::unary_function<std::string,bool> {
    bool operator ()( const std::string &s ) const
        { return firstIsAorZ( s ); }
};

int main() {
    std::remove_copy_if( std::istream_iterator<std::string>(std::cin), std::istream_iterator<std::string>(),
        std::ostream_iterator<std::string>(std::cout,"\n"),
        FirstIsAorZ() );
    
    return 0;
}
