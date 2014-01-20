#ifndef ALLOCANDINIT_H
#define ALLOCANDINIT_H

#include <algorithm>

template <typename T, typename In>
T *allocAndInit( std::size_t n, In b, In e ) {
    T *buf = static_cast<T *>(::operator new( n*sizeof(T) ));
    try {
        std::uninitialized_copy( b, e, buf );
        return buf;
    }
    catch( ... ) {
        ::operator delete( buf );
        throw;
    }
}

#endif
