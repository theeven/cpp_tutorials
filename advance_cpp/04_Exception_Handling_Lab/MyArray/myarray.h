#ifndef MYARRAY_H
#define MYARRAY_H

#include <algorithm>

template <class T>
class MyArray {
  public:
    MyArray( const T &, std::size_t len );
    MyArray( const MyArray & );
    MyArray &operator =( const MyArray & );
    
    void swap( MyArray &that );
    
    bool operator ==( const MyArray &rhs ) const;
    bool operator <( const MyArray &rhs ) const;
    bool operator !=( const MyArray &rhs ) const
    	{ return !(*this == rhs); }
    bool operator >=( const MyArray &rhs ) const
    	{ return !(*this < rhs); }
    bool operator >( const MyArray &rhs ) const
    	{ return rhs < *this; }
    bool operator <=( const MyArray &rhs ) const
    	{ return !(rhs < *this); }
    
	T &operator []( int i )
        { return a_[i]; }
    const T &operator []( int i ) const
        { return a_[i]; }
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

template <class T> // EXCEPTION SAFE?
MyArray<T>::MyArray( const T &val, std::size_t size )
	: a_(new T[size]), size_(size) {
    for( int i = 0; i < size; ++i )
        a_[i] = val;
}

template <class T> // EXCEPTION SAFE?
MyArray<T>::MyArray( const MyArray &that )
	: a_( new T[that.size()]), size_(that.size()) {
    for( int i = 0; i < size_; ++i )
        a_[i] = that[i];
}

template <class T> // EXCEPTION SAFE?
MyArray<T> &MyArray<T>::operator =( const MyArray &rhs ) {
	delete [] a_;
	a_ = new T[size_ = rhs.size()];
    for( int i = 0; i < size_; ++i )
    	a_[i] = rhs[i];
    return *this;
}

template <class T> // EXCEPTION SAFE?
void MyArray<T>::swap( MyArray &that ) {
    MyArray temp( *this );
    *this = that;
    that = temp;
}

template <class T>
bool MyArray<T>::operator ==( const MyArray &rhs ) const {
	if( size_ != rhs.size_ )
		return false;
    return std::equal( a_, a_+size_, rhs.a_ );
}

template <class T>
bool MyArray<T>::operator <( const MyArray &rhs ) const
	{ return std::lexicographical_compare( a_, a_+size_, rhs.a_, rhs.a_+rhs.size_ ); }

#endif
