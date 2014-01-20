#include <iostream>
#include "rational.h"

void Rational::normalize() {
	int a = n_<0?-n_:n_;
	int b = d_<0?-d_:d_;
	while( b != 0 ) { // Euclid's algorithm
		int z = a%b;
		a = b;
		b = z;
	}
	n_ /= a;
	d_ /= a;
}

Rational &Rational::operator +=( const Rational &rhs ) {
	n_ = n_ * rhs.d_ + rhs.n_ * d_;
	d_ = d_ * rhs.d_;
	normalize();
	return *this;
}

Rational &Rational::operator -=( const Rational &rhs ) {
	n_ = n_ * rhs.d_ - rhs.n_ * d_;
	d_ = d_ * rhs.d_;
	normalize();
	return *this;
}

Rational &Rational::operator *=( const Rational &rhs ) {
	n_ *= rhs.n_;
	d_ *= rhs.d_;
	normalize();
	return *this;
}

Rational &Rational::operator /=( const Rational &rhs ) {
	n_ *= rhs.d_;
	d_ *= rhs.n_;
	normalize();
	return *this;
}

std::ostream &operator <<( std::ostream &o, const Rational &r )
	{ return o << r.numerator() << '/' << r.denominator(); }

std::istream &operator >>( std::istream &i, Rational &r ) {
	int n;
	i >> n;
	char c;
	i >> c;
	int d;
	i >> d;
	r = Rational( n, d );
	return i;
}
