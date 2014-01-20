#ifndef ZEROOUT_H
#define ZEROOUT_H

//	This version of zeroOut uses template argument
//	deduction to deduce the length of an array argument.
template <int bound, typename T>
inline void zeroOut( T (&ary)[bound] ) {
    for( int i = 0; i < bound; ++i )
        ary[i] = T();
}

#endif
