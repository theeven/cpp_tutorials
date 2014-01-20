#ifndef SHAPE_H
#define SHAPE_H

// The tried and true Shape hierarchy!

class Shape {
  public:
	virtual ~Shape() {}
	virtual void draw() const = 0;
};

#endif
