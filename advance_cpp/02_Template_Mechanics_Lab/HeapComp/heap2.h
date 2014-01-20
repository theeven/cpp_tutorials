#ifndef HEAP2_H
#define HEAP2_H

#include <algorithm>
#include <vector>

template <typename T, typename Comp>
class Heap2 {
  public:
    Heap2()
    	: comp_(Comp()) {}
    ~Heap2()
    	{}
    Heap2( Comp comp )
    	: comp_(comp) {}
    void push( const T &val );
    T pop();
    bool empty() const
    	{ return h_.empty(); }
  private:
    Comp comp_;
    std::vector<T> h_;
};

template <typename T, typename Comp>
void Heap2<T,Comp>::push( const T &val ) {
    h_.push_back(val);
    std::push_heap( h_.begin(), h_.end(), comp_ );
}

template <typename T, typename Comp>
T Heap2<T,Comp>::pop() {
    std::pop_heap( h_.begin(), h_.end(), comp_ );
    T tmp( h_.back() );
    h_.pop_back();
    return tmp;
}

#endif
