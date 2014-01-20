#ifndef MYARRAY2_H
#define MYARRAY2_H

//
//	This includes a rewrite of MyArray (as MyArray2) to
//	be exception safe (and somewhat more efficient).
//

#include <algorithm>
#include <stdexcept>

struct BadIndex : public std::out_of_range {
	BadIndex() : std::out_of_range( "bad array index" ) {}
};

template <class T>
class MyArray2 {
  public:
    MyArray2( const T &, std::size_t len );
    MyArray2( const MyArray2 & );
    MyArray2 &operator =( const MyArray2 & );
    
    void swap( MyArray2 &that );
    
    bool operator ==( const MyArray2 &rhs ) const;
    bool operator <( const MyArray2 &rhs ) const;
    bool operator !=( const MyArray2 &rhs ) const
    	{ return !(*this == rhs); }
    bool operator >=( const MyArray2 &rhs ) const
    	{ return !(*this < rhs); }
    bool operator >( const MyArray2 &rhs ) const
    	{ return rhs < *this; }
    bool operator <=( const MyArray2 &rhs ) const
    	{ return !(rhs < *this); }
    
	T &operator []( int i )
        { return a_[i]; }
    const T &operator []( int i ) const
        { return a_[i]; }
    
    // Exercise 5
    // We call the index operations "at" in imitation of similar
    // operations in the standard library.
    // The exception type is derived from out_of_range, which is the
    // exception thrown by the standard library "at" operations.
    T &at( int i ) {
    	if( i >=size_ || i < 0 )
    		throw BadIndex();
        return a_[i];
    }
    const T &at( int i ) const {
    	if( i >=size_ || i < 0 )
    		throw BadIndex();
        return a_[i];
    }
    
    operator T *()
        { return a_; }
    operator const T *() const
        { return a_; }
    
    std::size_t size() const
    	{ return size_; }
  private:
    T *a_;
    std::size_t size_;
};

//	It's probably better to allocate a non-array and use the
// copy ctor to initialize each element.
template <class T>
MyArray2<T>::MyArray2( const T &val, std::size_t size )
	: a_(static_cast<T *>(::operator new(sizeof(T)*size))), size_(size) {
    try {
    	std::uninitialized_fill_n(a_,size_,val);
    }
    catch( ... ) {
    	::operator delete( a_ );
    	throw;
    }
}

//	Same comment as above.
template <class T>
MyArray2<T>::MyArray2( const MyArray2 &that )
	: a_(static_cast<T *>(::operator new(sizeof(T)*that.size()))), size_(that.size()) {
    try {
    	std::uninitialized_copy(that.a_,that.a_+size_,a_);
    }
    catch( ... ) {
    	::operator delete( a_ );
    	throw;
    }
}

template <class T>
// Here, we do things that might cause an exception first,
// then change the state of the object.
// We also are more careful in copying.
MyArray2<T> &MyArray2<T>::operator =( const MyArray2 &rhs ) {
	// First, things that can throw.  Copy the source buffer.
	T *temp = static_cast<T *>(::operator new( sizeof(T)*rhs.size() ));
    try {
    	std::uninitialized_copy(rhs.a_,rhs.a_+rhs.size_,temp);
    }
    catch( ... ) {
    	::operator delete( temp );
    	throw;
    }
    
    // Now, clean up the old buffer; can't throw.
    for( int i = 0; i < size_; ++i )
    	a_[i].~T();
    ::operator delete( a_ );
    
    // Finally, change the state of the object with non-throwing operations.
    size_ = rhs.size_;
	a_ = temp;
	
    return *this;
}

template <class T>
// Here, we do a fast swap, using exception safe swaps of
// the individual data members of the arrays.
void MyArray2<T>::swap( MyArray2 &that ) {
    std::swap( a_, that.a_ );
    std::swap( size_, that.size_ );
}

template <class T>
bool MyArray2<T>::operator ==( const MyArray2 &rhs ) const {
	if( size_ != rhs.size_ )
		return false;
    return std::equal( a_, a_+size_, rhs.a_ );
}

template <class T>
bool MyArray2<T>::operator <( const MyArray2 &rhs ) const
	{ return std::lexicographical_compare( a_, a_+size_, rhs.a_, rhs.a_+rhs.size_ ); }

#endif
