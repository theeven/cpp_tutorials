#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>

class Shape {
  public:
	virtual ~Shape() {}
	friend std::ostream &operator <<( std::ostream &o, const Shape &s )
		{ return s.id( o ); }
  private:
	virtual std::ostream &id( std::ostream & ) const = 0;
};

class Circle : public Shape {
  public:
	Circle() { ++count_; }
  private:
	std::ostream &id( std::ostream &o ) const { return o << "C" << count_; }
	static long count_;
};
long Circle::count_ = 0;

class Square : public Shape {
  public:
	Square() { ++count_; }
  private:
	std::ostream &id( std::ostream &o ) const { return o << "S" << count_; }
	static long count_;
};
long Square::count_ = 0;


class Triangle : public Shape {
  public:
	Triangle() { ++count_; }
  private:
	std::ostream &id( std::ostream &o ) const { return o << "T" << count_; }
	static long count_;
};
long Triangle::count_ = 0;


#endif
