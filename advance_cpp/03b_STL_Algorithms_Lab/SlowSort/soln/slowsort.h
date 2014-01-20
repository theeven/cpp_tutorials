#ifndef SLOWSORT_H
#define SLOWSORT_H

#include <functional>

template <class For>
void slow_sort( For s, For e ) {
	for( For i(s); i != e; ++i )
		for( For j(i); j != e; ++j )
			if( *j < *i )
				std::iter_swap( i, j );
}

template <class For>
void bubble_sort( For s, For e ) {
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



#endif
