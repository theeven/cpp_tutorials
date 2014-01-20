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
	//Circle() { std::cout << "make Circle #" << ++count_ << std::endl; }
	//~Circle() { std::cout << "destroy Circle #" << count_ << std::endl; }
  private:
	std::ostream &id( std::ostream &o ) const { return o << "Circle." << count_; }
	static long count_;
};
long Circle::count_ = 0;

class Square : public Shape {
  public:
	Square() { ++count_; }
	//Square() { std::cout << "make Square #" << ++count_ << std::endl; }
	//~Square() { std::cout << "destroy Square #" << count_ << std::endl; }
  private:
	std::ostream &id( std::ostream &o ) const { return o << "Square." << count_; }
	static long count_;
};
long Square::count_ = 0;


class Triangle : public Shape {
  public:
	Triangle() { ++count_; }
	//Triangle() { std::cout << "make Triangle #" << ++count_ << std::endl; }
	//~Triangle() { std::cout << "destroy Triangle #" << count_ << std::endl; }
  private:
	std::ostream &id( std::ostream &o ) const { return o << "Triangle." << count_; }
	static long count_;
};
long Triangle::count_ = 0;


#endif
