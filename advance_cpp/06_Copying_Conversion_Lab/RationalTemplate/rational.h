#ifndef RATIONAL_H
#define RATIONAL_H

#include <iosfwd>

class Rational {
  public:
	Rational( int n = 0, int d = 1 )
		: n_(n), d_(d) {}
	~Rational()
		{}
	// Rational( const Rational &that );
	// Rational &operator =( const Rational &rhs );
	int numerator() const
		{ return n_; }
	int denominator() const
		{ return d_; }
  private:
	int n_, d_;
};

inline Rational operator *( const Rational &lhs, const Rational &rhs )
	{ return Rational( lhs.numerator()*rhs.numerator(), lhs.denominator()*rhs.denominator() ); }

inline bool operator <( const Rational &lhs, const Rational &rhs )
	{ return double(lhs.numerator())/lhs.denominator() < double(rhs.numerator())/rhs.denominator(); }

inline bool operator ==( const Rational &lhs, const Rational &rhs )
	{ return double(lhs.numerator())/lhs.denominator() == double(rhs.numerator())/rhs.denominator(); }

std::ostream &operator <<( std::ostream &, const Rational & );
std::istream &operator >>( std::istream &, Rational & );

#endif
