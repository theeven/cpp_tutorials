#ifndef CPTR_INST_H
#define CPTR_INST_H

#include <iostream>
#include <map>

// For exercise #6; Cptr hacked to report on its operations.

template <class T>
class Cptr {
  public:
    Cptr( T *p ) : p_( p ), c_( new long( 1 ) )
    	{ ptrs_[(void *)this] = ++count_; std::cout << "creating\t" << *this << std::endl; }
    ~Cptr() {
    	std::cout << "destroying\t" << *this << std::flush;
    	if( !--*c_ ) {
    		std::cout << " and its object" << std::flush;
    		delete c_;
    		delete p_;
    	}
    	std::cout << std::endl;
    }
    Cptr( const Cptr &init )
    	: p_( init.p_ ), c_( init.c_ ) {
    		ptrs_[(void *)this] = ++count_;
    		std::cout << "copy ctor\t" << *this << '(' << init << ')' << std::endl;
    		++*c_;
    	}
    Cptr &operator =( const Cptr &rhs ) {
        std::cout << "assigning\t" << *this << " = " << rhs << std::endl;
        if( this != &rhs ) {
            if( !--*c_ ) { delete c_; delete p_; }
            p_ = rhs.p_;
            ++*(c_ = rhs.c_);
        }
        return *this;
    }
    T &operator *( ) const
    	{ return *p_; }
    T *operator ->( ) const
    	{ return p_; }
    friend std::ostream &operator <<( std::ostream &o, const Cptr &ptr )
    	{ return o << "Cptr<" << typeid(T).name() << '>' << Cptr::ptrs_[(void *)&ptr] << ":\t" << *ptr.p_ << " [" << *ptr.c_ << ']'; }
  private:
    T *p_;
    long *c_;
    static std::map<void *, long> ptrs_;
    static long count_;
};

template <typename T>
std::map<void *, long> Cptr<T>::ptrs_;

template <typename T>
long Cptr<T>::count_ = 0;

#endif
