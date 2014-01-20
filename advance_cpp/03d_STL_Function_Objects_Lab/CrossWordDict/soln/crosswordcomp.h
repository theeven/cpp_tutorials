#ifndef CROSSWORDCOMP_H
#define CROSSWORDCOMP_H

//
//	Answer to Quiz #1 on page 10.
//

#include <cstring>

inline bool
crosswordComp( const char *a, const char *b ) {
    if( std::strlen( a ) < std::strlen( b ) ) return true;
    if( std::strlen( a ) > std::strlen( b ) ) return false;
    return std::strcmp( a, b ) < 0;
}

struct CrosswordComp : public std::binary_function<const char *,const char *,bool> {
    bool operator ()( const char *a, const char *b ) const
        { return crosswordComp( a, b ); }
};

#endif
