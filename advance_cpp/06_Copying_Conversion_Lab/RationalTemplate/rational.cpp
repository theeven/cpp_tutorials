#include <iostream>
#include "rational.h"

using std::ostream;
using std::istream;

ostream &operator <<( ostream &o, const Rational &r ) {
	return o << r.numerator() << '/' << r.denominator();
}

istream &operator >>( istream &i, Rational &r ) {
	int n;
	i >> n;
	char c;
	i >> c;
	int d;
	i >> d;
	r = Rational( n, d );
	return i;
}
