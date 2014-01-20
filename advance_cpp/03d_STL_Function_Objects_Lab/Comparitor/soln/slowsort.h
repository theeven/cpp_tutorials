#ifndef SLOWSORT_H
#define SLOWSORT_H

//	EXERCISE #2

#include <functional>
#include <algorithm>

template <class For>
void slowsort( For s, For e ) {
	for( For i(s); i != e; ++i )
		for( For j(i); j != e; ++j )
			if( *j < *i )
				std::iter_swap( i, j );
}

template <class For, class Comp>
void slowsort( For s, For e, Comp c ) {
	for( For i(s); i != e; ++i )
		for( For j(i); j != e; ++j )
			if( c(*j, *i) )
				std::iter_swap( i, j );
}

//
//	We're throwing in a bubble sort, just for fun.
//

template <class For>
void bubblesort( For s, For e ) {
	bool changed;
	do {
		changed = false;
		For t;
		For ss( s );
		while( t=ss++, ss != e )
			if( *ss < *t ) {
				std::iter_swap( ss, t );
				changed = true;
			}
	} while( changed );
}

template <class For, class Comp>
void bubblesort( For s, For e, Comp c ) {
	bool changed;
	do {
		changed = false;
		For t;
		For ss( s );
		while( t=ss++, ss != e )
			if( c(*ss, *t) ) {
				std::iter_swap( ss, t );
				changed = true;
			}
	} while( changed );
}

#endif
