#ifndef SSOSTRING_H
#define SSOSTRING_H

#include <cstring>

template <int ssosize = 15>
class SSOString {
  public:
	SSOString( const char * ); // Q: Should this ctor be explicit?
	SSOString( const SSOString & ); // Q: Why do we need a copy ctor when we have the template below?
	
	// This member template ctor handles most conversions among SSOStrings with different sizes.
	// Q: Is efficient enough, or should we avoid these conversions?
	template <int n>
	SSOString( const SSOString<n> &);
	
	// Q: Why is there no member template corresponding to this copy assignment?
	// Q: How is an assignment between SSOStrings of different sizes accomplished?
	// Q: Should we define a member template anyway?
	SSOString &operator =( const SSOString & );
	
	// Q: Why isn't this a virtual destructor?
	~SSOString();
	
	// Q: Why is operator == implemented as a non-member, non-template function?
	// Q: Why doesn't this operator == doesn't allow us to compare SSOStrings of different sizes?
	// Q: Should we allow such comparisons, and if so, how would we implement them?
	// Note: Ordinarily there would be implementations of all the equality an relational operators,
	// but they are ommitted for space.
	friend bool operator ==( const SSOString &lhs, const SSOString &rhs )
		{ return std::strcmp( lhs.get(), rhs.get() ) == 0; }
	
	SSOString &operator +=( const SSOString & );
	
	// This is a non-template friend for exact matches, and conversions from const char *.
	// Q: Should we overload to avoid conversions?
	// Q: Why must this function be defined in the class template?
	friend SSOString operator +( const SSOString &lhs, const SSOString &rhs ) {
		SSOString temp( lhs );
		temp += rhs;
		return temp;
	}
	
	// Q: Why are the index operators overloaded?
	char &operator []( int );
	const char &operator []( int ) const;
	
	int size() const;
	void swap( SSOString & );
	
	// Q: Should we provide a conversion operator to const char * instead?
	const char *get() const;
  private:
  	void doInit( const char * );
	union Rep {
		char b_[ssosize+1 ];
		char *s_;
	} rep_;
	bool sso_; // true => using sso, not heap
};

// This is a template for exact matches for SSOStrings with different template arguments.
// Conversions are handled by the non-template version of operator + defined in the class.
// Q: Why can't a function template be used for conversions?
template <int a, int b>
SSOString<a> operator +( const SSOString<a> &lhs, const SSOString<b> &rhs ) {
		SSOString<a> temp( lhs );
		temp += rhs;
		return temp;
}

// Note that swap requires same type of SSOStrings.
// Q: Is this too restrictive, or is it a feature?
template <int ssosize>
void SSOString<ssosize>::swap( SSOString &that ) {
	if( sso_ ) {
		if( that.sso_ ) {
			std::swap( rep_, that.rep_ );
		}
		else {
			Rep tmp( rep_ );
			rep_.s_ = that.rep_.s_;
			that.rep_ = tmp;
			std::swap( sso_, that.sso_ );
		}
	}
	else {
		if( that.sso_ ) {
			Rep tmp( that.rep_ );
			that.rep_.s_ = rep_.s_;
			rep_ = tmp;
			std::swap( sso_, that.sso_ );
		}
		else {
			std::swap( rep_.s_, that.rep_.s_ );
		}
	}
}

template <int ssosize>
inline const char *SSOString<ssosize>::get() const
	{ return sso_ ? rep_.b_ : rep_.s_; }

template <int ssosize>
inline int SSOString<ssosize>::size() const
	{ return std::strlen( get() ); }

template <int ssosize>
inline char &SSOString<ssosize>::operator []( int i )
	// Q: Is this a safe cast?  Is there a better alternative?
	{ return const_cast<char &>(get()[i]); }

template <int ssosize>
inline const char &SSOString<ssosize>::operator []( int i ) const
	{ return get()[i]; }

template <int ssosize>
void SSOString<ssosize>::doInit( const char *init ) {
	std::size_t len = std::strlen(init);
	sso_ = (len <= ssosize);
	if( sso_ )
		std::strcpy( rep_.b_, init );
	else
		std::strcpy( rep_.s_ = new char[len+1], init );
}

template <int ssosize>
SSOString<ssosize>::SSOString( const char *str ) {
	if( !str ) str = "";
	doInit( str );
}

template <int ssosize>
SSOString<ssosize>::SSOString( const SSOString &that ) : sso_(that.sso_) {
	if( sso_ )
		rep_ = that.rep_;
	else
		rep_.s_ = std::strcpy( new char[std::strlen(that.rep_.s_)+1], that.rep_.s_ );
}

template <int ssosize>
template <int n>
SSOString<ssosize>::SSOString( const SSOString<n> &that )
	{ doInit( that.get() ); }

template <int ssosize>
SSOString<ssosize>::~SSOString() {
	if( !sso_ )
		delete [] rep_.s_;
}

template <int ssosize>
SSOString<ssosize> &SSOString<ssosize>::operator =( const SSOString &rhs ) {
	SSOString temp( rhs.get() );
	swap( temp );
	return *this;
}

template <int ssosize>	
SSOString<ssosize> &SSOString<ssosize>::operator +=( const SSOString &rhs ) {
	const char *firstPart = get();
	const char *toAppend = rhs.get();
	const int newSize = std::strlen(firstPart) + std::strlen(toAppend);

	if( sso_ ) {
		if( newSize <= ssosize )
			std::strcat( rep_.b_, toAppend );
		else {
			char *temp = new char[newSize+1];
			std::strcat( std::strcpy( temp, firstPart ), toAppend );
			rep_.s_ = temp;
			sso_ = false;
		}
	}
	else {
		char *temp = new char[newSize+1];
		std::strcat( std::strcpy( temp, firstPart ), toAppend );
		delete [] rep_.s_;
		rep_.s_ = temp;
	}
	return *this;
}

#endif
