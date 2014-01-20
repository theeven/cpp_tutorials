#ifndef HEAP1_H
#define HEAP1_H

#include <algorithm>
#include <functional>
#include <vector>


//
//	Here, we're just going to declare (not define) the primary
//	so that we know we'll always pick up the partial specialization.
//	If we try to specialize Heap for a non-pointer type, we'll get
//	a compile time error.
//	Ordinarily, we'd implement the primary.
//
template <typename T>
class Heap;

//
//	First a declaration of a complete specialization for void *.
//	This will cause an error if a Heap of void *s is declared.
//	Alternatively, we could decide how a Heap of void *s should
//	behave and implement it.
//	This version (#ifdeffed out) just compares the address for void *.
//

template <>
class Heap<void *>;

#if 0
template <>
class Heap<void *> {
  public:
    void push( void *val );
    void *pop();
    bool empty() const { return h_.empty(); }
  private:
    std::vector<void *> h_;
};

void Heap<void *>::push( void *pval ) {
    if( pval ) {
        h_.push_back(pval);
        std::push_heap( h_.begin(), h_.end() );
    }
}

void *Heap<void *>::pop() {
    std::pop_heap( h_.begin(), h_.end() );
    void *tmp( h_.back() );
    h_.pop_back();
    return tmp;
}
#endif

//
//	This is the exercise solution:
//
//	Note that the primary is declared above.
//

//	This is a base class that will be used as common implementation
//	of all the partial specializations for pointer elements.
class PtrHeapBase {
  public:
	PtrHeapBase( bool (*comp)(const void *, const void *) )
		: comp_(comp) {}
    void push( const void *val );
    const void *pop();
    bool empty() const { return h_.empty(); }
  private:
	bool (*comp_)(const void *, const void *);
    std::vector<const void *> h_;
};

void PtrHeapBase::push( const void *pval ) {
    if( pval ) {
        h_.push_back(pval);
        std::push_heap( h_.begin(), h_.end(), comp_ );
    }
}

const void *PtrHeapBase::pop() {
    std::pop_heap( h_.begin(), h_.end(), comp_ );
    const void *tmp( h_.back() );
    h_.pop_back();
    return tmp;
}

//	Now, a partial specialization that uses the base class.
//	Each instantiation should cause just a copy of Heap<T *>::comp_
//	to be instantiated.
template <typename T>
class Heap<T *> : public PtrHeapBase {
  public:
	Heap()
		: PtrHeapBase(comp_) {}
    void push( T *val )
    	{ PtrHeapBase::push( val ); }
    T *pop()
    	{ return static_cast<T *>(PtrHeapBase::pop()); }
  private:
    static bool comp_( const void *a, const void *b )
    	{ return *static_cast<T *>(a) < *static_cast<T *>(b); }
};

#endif
