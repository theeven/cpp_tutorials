#ifndef ARRAY_H
#define ARRAY_H

//
//	We'll just reuse the implementation of MyArray2 (from the exception module)
//	and forward the operations to it.  This should reduce to zero code bloat
//	from different specializations of Array with the same element type but
//	different sizes.
//

#include "myarray2.h"

template <class T, int n>
class Array {
  public:
    Array( const T &val ) 
    	: impl_(val,n) {}
    Array( const Array &that )
    	: impl_(that) {}
    Array &operator =( const Array &rhs )
    	{ impl_.operator =(rhs.impl_); return *this; }
    
    void swap( Array &that )
    	{ impl_.swap(that); }
    
    bool operator ==( const Array &rhs ) const
    	{ return impl_.operator ==(rhs.impl_); }
    bool operator <( const Array &rhs ) const
    	{ return impl_.operator <(rhs.impl_); }
    bool operator !=( const Array &rhs ) const
    	{ return !(*this == rhs); }
    bool operator >=( const Array &rhs ) const
    	{ return !(*this < rhs); }
    bool operator >( const Array &rhs ) const
    	{ return rhs < *this; }
    bool operator <=( const Array &rhs ) const
    	{ return !(rhs < *this); }
    
	T &operator []( int i )
        { return impl_.operator[](i); }
    const T &operator []( int i ) const
        { return impl_.operator[](i); }
    
    T &at( int i )
        { return impl_.at(i); }
    const T &at( int i ) const
        { return impl_.at(i); }

    // Note conversion operators removed.
    // These were probably not a good idea in the
    // case of MyArray2, but here they would effectively allow
    // us to compare Arrays with different values of n.
    //operator T *()
    T *asPointer() // this explicit conversion function is a lot safer
        { return impl_.operator T *(); }
    //operator const T *() const
    const T *asPointerToConst() const // ditto
        { return impl_.operator const T *(); }
    
    std::size_t size() const
    	{ return n; }
  private:
	MyArray2<T> impl_;
};

#endif
