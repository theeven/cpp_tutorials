#ifndef TRATIONAL_H
#define TRATIONAL_H

//
//	A template-based rational number implementation.
//	This time, we made some attempt at normalization
//	of the numerator and denominator.
//
#include <iostream>

template <typename T>
T GCD( T a,  T b ) { // Euclid's algorithm
	while( b != 0 ) {
		T z = a%b;
		a = b;
		b = z;
	}
	return a;
}

template <typename T>
class R {
  public:
	R( const T &n = 0, const T &d = 1 ) : n_(n), d_(d)
		{ normalize(); }
	~R()
		{}
	R( const R &that )
		: n_(that.n_), d_(that.d_) {}
	R &operator =( const R &rhs ) {
		n_ = rhs.n_;
		d_ = rhs.d_;
		return *this;
	}
	
	// Notice that the binary operators are defined as non-template friends, INSIDE
	// the class template.  This is an application of the "making new friends" idiom.
	friend R operator +( const R &lhs, const R &rhs ) {
		T d = lhs.denominator()*rhs.denominator();
		T n = lhs.numerator()*rhs.denominator() + rhs.numerator()*lhs.denominator();
		return R(n,d);
	}
	
	friend R operator *( const R &lhs, const R &rhs ) {
		T n = lhs.numerator()*rhs.numerator();
		T d = lhs.denominator()*rhs.denominator();
		return R(n,d);
	}

	friend bool operator <( const R &lhs, const R &rhs )
		{ return lhs.numerator()*rhs.denominator() < rhs.numerator()*lhs.denominator(); }
	friend bool operator ==( const R &lhs, const R &rhs )
		{ return lhs.numerator()*rhs.denominator() == rhs.numerator()*lhs.denominator(); }

	const T &numerator() const
		{ return n_; }
	const T &denominator() const
		{ return d_; }
  private:
	void normalize() {
		T gcd( GCD(n_>=0?n_:-n_,d_>=0?d_:-d_) );
		n_ /= gcd;
		d_ /= gcd;
	}
	T n_, d_;
};


template <typename T>
std::ostream &operator <<( std::ostream &o, const R<T> &r )
	{ return o << r.numerator() << '/' << r.denominator(); }

template <typename T>
std::istream &operator >>( std::istream &i, R<T> &r ) {
	T n;
	i >> n;
	char c;
	i >> c;
	T d;
	i >> d;
	r = R<T>( n, d );
	return i;
}


//
// A complete specialization for the case where the underlying type is int.
// A fancier implementation would probably specialize for any predefined
// integral type (except bool!)
//
template <>
class R<int> {
  public:
	R( int n = 0, int d = 1 ) {
		T gcd( GCD(n,d));
		n_ = n/gcd;
		d_ = d/gcd;
	}
	~R()
		{}
	R( const R &that )
		: n_(that.n_), d_(that.d_) {}
	R &operator =( const R &rhs ) {
		n_ = rhs.n_;
		d_ = rhs.d_;
		return *this;
	}
	
	// These binary operators don't have to be defined inside
	// the class, and don't have to be friends.  But I left
	// them here anyway...
	friend R operator +( R lhs, R rhs ) {
		T d = lhs.denominator()*rhs.denominator();
		T n = lhs.numerator()*rhs.denominator()+rhs.numerator()*lhs.denominator();
		T gcd( GCD(n,d) );
		return R(n/gcd,d/gcd);
	}
	
	friend R operator *( R lhs, R rhs ) {
		int n = lhs.numerator()*rhs.numerator();
		int d = lhs.denominator()*rhs.denominator();
		int gcd( GCD(n,d) );
		return R(n/gcd,d/gcd);
	}

	friend bool operator <( R lhs, R rhs )
		{ return double(lhs.numerator())/lhs.denominator() < double(rhs.numerator())/rhs.denominator(); }

	friend bool operator ==( R lhs, R rhs )
		{ return double(lhs.numerator())/lhs.denominator() == double(rhs.numerator())/rhs.denominator(); }

	int numerator() const
		{ return n_; }
	int denominator() const
		{ return d_; }
  private:
	int n_, d_;
};

#endif
