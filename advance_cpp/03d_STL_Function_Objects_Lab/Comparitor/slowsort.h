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

#endif
