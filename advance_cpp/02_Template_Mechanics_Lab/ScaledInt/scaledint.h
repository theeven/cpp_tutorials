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

#endif
