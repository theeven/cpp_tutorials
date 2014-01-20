#ifndef RATIONAL_H
#define RATIONAL_H

#include <iosfwd>

class Rational {
  public:
	Rational( int n = 0, int d = 1 )
		: n_(n), d_(d) { normalize(); }
	~Rational()
		{}
	// Rational( const Rational &that );
	// Rational &operator =( const Rational &rhs );
	int numerator() const
		{ return n_; }
	int denominator() const
		{ return d_; }
	double toDouble() const
		{ return double(n_)/d_; }
	Rational &operator +=( const Rational &rhs );
	Rational &operator -=( const Rational &rhs );
	Rational &operator *=( const Rational &rhs );
	Rational &operator /=( const Rational &rhs );
  private:
	void normalize();
	int n_, d_;
};

inline Rational operator +( const Rational &lhs, const Rational &rhs )
	{ Rational temp( lhs ); return temp += rhs; }

inline Rational operator -( const Rational &lhs, const Rational &rhs )
	{ Rational temp( lhs ); return temp -= rhs; }
	
inline Rational operator *( const Rational &lhs, const Rational &rhs )
	{ Rational temp( lhs ); return temp *= rhs; }

inline Rational operator /( const Rational &lhs, const Rational &rhs )
	{ Rational temp( lhs ); return temp /= rhs; }

inline bool operator <( const Rational &lhs, const Rational &rhs )
	{ return lhs.numerator()*rhs.denominator() < rhs.numerator()*lhs.denominator(); }

inline bool operator >( const Rational &lhs, const Rational &rhs )
	{ return rhs < lhs; }

inline bool operator >=( const Rational &lhs, const Rational &rhs )
	{ return !(lhs < rhs); }

inline bool operator <=( const Rational &lhs, const Rational &rhs )
	{ return !(rhs < lhs); }

inline bool operator ==( const Rational &lhs, const Rational &rhs )
	{ return lhs.numerator()*rhs.denominator() == rhs.numerator()*lhs.denominator(); }

inline bool operator !=( const Rational &lhs, const Rational &rhs )
	{ return !(lhs == rhs); }

std::ostream &operator <<( std::ostream &, const Rational & );
std::istream &operator >>( std::istream &, Rational & );

#endif
