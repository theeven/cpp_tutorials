#include <iostream>
#include <iterator>

template< typename In1, typename In2, typename Out>
Out interleave( In1 first1, In1 last1, In2 first2, In2 last2, Out result ) {
    while( first1 != last1 && first2 != last2 ) {
        *result++ = *first1++;
        *result++ = *first2++;
    }
    return result;
}

template <typename T, std::size_t n>
std::size_t length( T (&)[n] ) { return n; }

int main() {
	int a[] = { 1,2,3,4,5 };
	float b[] = { 1.1, 2.2, 3.3, 4.4 };
	interleave( a, a+length(a), b, b+length(b), std::ostream_iterator<double>(std::cout,"\n") );
	
	return 0;
}
