#ifndef SCALEDINT_H
#define SCALEDINT_H

class ScaledInteger {
  public:
	enum { factor = 100 };
	ScaledInteger()
		: d_(0) {}
	ScaledInteger( int i )
		: d_(i*factor) {}
	// compiler-generated copy operations...
	ScaledInteger &operator +=( ScaledInteger rhs )
		{ d_ += rhs.d_; return *this; }
	friend ScaledInteger operator +( ScaledInteger a, ScaledInteger b )
		{ ScaledInteger tmp( a ); return tmp += b; }
	
	ScaledInteger &operator -=( ScaledInteger rhs )
		{ d_ -= rhs.d_; return *this; }
	friend ScaledInteger operator -( ScaledInteger a, ScaledInteger b )
		{ ScaledInteger tmp( a ); return tmp -= b; }
	
	ScaledInteger &operator *=( ScaledInteger rhs ) {
		d_ = (d_ * rhs.d_) / factor;
		return *this;
	}
	friend ScaledInteger operator *( ScaledInteger a, ScaledInteger b )
		{ ScaledInteger tmp( a ); return tmp *= b; }
	
	ScaledInteger &operator /=( const ScaledInteger &rhs ) {
		d_ = (d_ * factor) / rhs.d_;
		return *this;
	}
	friend ScaledInteger operator /( ScaledInteger a, ScaledInteger b )
		{ ScaledInteger tmp( a ); return tmp /= b; }
  private:
	friend std::ostream &operator <<( std::ostream &o, ScaledInteger i )
		{ return o << (i.d_/factor) << '.' << (i.d_%factor); }
	int d_;
};

// Compile-time calculation of 10**n that uses recursive
// class template instantiation!
//
template <int n>
struct Pow
	{ enum { r = Pow<n-1>::r * 10 }; };

template <>
struct Pow<1>
	{ enum { r = 10 }; };

template <int digits, typename Int = long>
class ScaledInt {
  public:
	enum { factor = Pow<digits>::r };
	typedef Int IntegerType;
	ScaledInt()
		: d_(0) {}
	ScaledInt( Int i )
		: d_(i*factor) {}
	// compiler-generated copy operations...
	ScaledInt &operator +=( ScaledInt rhs )
		{ d_ += rhs.d_; return *this; }
	friend ScaledInt operator +( ScaledInt a, ScaledInt b )
		{ ScaledInt tmp( a ); return tmp += b; }
	
	ScaledInt &operator -=( ScaledInt rhs )
		{ d_ -= rhs.d_; return *this; }
	friend ScaledInt operator -( ScaledInt a, ScaledInt b )
		{ ScaledInt tmp( a ); return tmp -= b; }
	
	ScaledInt &operator *=( ScaledInt rhs ) {
		d_ = (d_ * rhs.d_) / factor;
		return *this;
	}
	friend ScaledInt operator *( ScaledInt a, ScaledInt b )
		{ ScaledInt tmp( a ); return tmp *= b; }
	
	ScaledInt &operator /=( const ScaledInt &rhs ) {
		d_ = (d_ * factor) / rhs.d_;
		return *this;
	}
	friend ScaledInt operator /( ScaledInt a, ScaledInt b )
		{ ScaledInt tmp( a ); return tmp /= b; }
  private:
	friend std::ostream &operator <<( std::ostream &o, ScaledInt i )
		{ return o << (i.d_/factor) << '.' << (i.d_%factor); }
	IntegerType d_;
};

#endif
