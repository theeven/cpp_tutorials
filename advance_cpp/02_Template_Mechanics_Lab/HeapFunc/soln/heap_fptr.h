#ifndef HEAP_FPTR_H
#define HEAP_FPTR_H

#include "heap.h"

//	Note that we may have portability issues for Heaps of pointer to
//	function.  To fix that, we'll have to do something similar to what
//	we did for pointers to data, above, but take into account functions
//	with different numbers of arguments.

//	This is a base class that will be used as common implementation
//	of all the partial specializations for pointer elements.

typedef void (*FunPtrType)();

class FunPtrHeapBase {
  public:
    void push( FunPtrType val );
    FunPtrType pop();
    bool empty() const { return h_.empty(); }
  private:
    std::vector<FunPtrType> h_;
};

void FunPtrHeapBase::push( FunPtrType val ) {
    if( val ) {
        h_.push_back(val);
        std::push_heap( h_.begin(), h_.end() );
    }
}

FunPtrType FunPtrHeapBase::pop() {
    std::pop_heap( h_.begin(), h_.end() );
    FunPtrType tmp( h_.back() );
    h_.pop_back();
    return tmp;
}

//	Now, a sequence of partial specializations for various function
//	arities.
template <typename R> // zero args
class Heap<R(*)()> : public FunPtrHeapBase {
  public:
	typedef R (*FP)();
    void push( FP val )
    	{ FunPtrHeapBase::push( val ); }
    FP pop()
    	{ return static_cast<FP>(FunPtrHeapBase::pop()); }
};

template <typename R, typename A> // one arg
class Heap<R(*)(A)> : public FunPtrHeapBase {
  public:
	typedef R (*FP)(A);
    void push( FP val )
    	{ FunPtrHeapBase::push( reinterpret_cast<FunPtrType>(val) ); }
    FP pop()
    	{ return reinterpret_cast<FP>(FunPtrHeapBase::pop()); }
};

template <typename R, typename A1, typename A2> // two args
class Heap<R(*)(A1,A2)> : public FunPtrHeapBase {
  public:
	typedef R (*FP)(A1,A2);
    void push( FP val )
    	{ FunPtrHeapBase::push( reinterpret_cast<FunPtrType>(val) ); }
    FP pop()
    	{ return reinterpret_cast<FP>(FunPtrHeapBase::pop()); }
};

//	...and so on for as many args as you like!

#endif
