#ifndef HEAP_H
#define HEAP_H

#include <algorithm>
#include <functional>
#include <vector>


//
//	The primary Heap template.
//

template <typename T>
class Heap {
  public:
    void push( const T &val );
    T pop();
    bool empty() const { return h_.empty(); }
  private:
    std::vector<T> h_;
};

template <typename T>
void Heap<T>::push( const T &val ) {
    h_.push_back(val);
    std::push_heap( h_.begin(), h_.end() );
}

template <typename T>
T Heap<T>::pop() {
    std::pop_heap( h_.begin(), h_.end() );
    T tmp( h_.back() );
    h_.pop_back();
    return tmp;
}

//
//	A straightforward implementation of the partial specialization
//	for pointers duplicates a lot of code for different
//	specializations.
//
template <typename T>
class Heap<T *> {
  public:
    void push( const T *val );
    T *pop();
    bool empty() const { return h_.empty(); }
  private:
    std::vector<T *> h_;
};

template <typename T>
struct PtrCmp : public std::binary_function<const T *, const T *, bool> {
    bool operator ()( const T *a, const T *b ) const
        { return *a < *b; }
};

template <typename T>
void Heap<T *>::push( const T *pval ) {
    if( pval ) {
        h_.push_back(pval);
        std::push_heap( h_.begin(), h_.end(), PtrCmp<T>() );
    }
}

template <typename T>
T *Heap<T *>::pop() {
    std::pop_heap( h_.begin(), h_.end(), PtrCmp<T>() );
    T *tmp( h_.back() );
    h_.pop_back();
    return tmp;
}

#endif
