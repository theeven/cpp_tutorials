#ifndef ZEROOUT_H
#define ZEROOUT_H

//	The template below requires that you pass the bound
//	explicitly.
template <typename T>
void zeroOut( T ary[], int bound ) {
    for( int i = 0; i < bound; ++i )
        ary[i] = T();
}

//	This version of zeroOut uses template argument
//	deduction to deduce the length of an array argument,
//	but is inline and forwards its implementation to the
//	two-argument version of zeroOut.  Safety for free.
template <int bound, typename T>
inline void zeroOut( T (&ary)[bound] )
	{ zeroOut( ary, bound ); }

#endif
