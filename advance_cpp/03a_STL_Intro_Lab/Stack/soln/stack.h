#ifndef STACK_H
#define STACK_H

#include <vector>

template <typename T>
class Stack {
  public:
    Stack()
        {}
    ~Stack()
        {}
    void push( const T &val )
        { s_.push_back( val ); }
    void pop()
        { s_.pop_back(); }
    const T &top() const
        { return s_.back(); }
    bool isEmpty() const
        { return s_.empty(); }
  private:
    std::vector<T> s_;
};


#endif
