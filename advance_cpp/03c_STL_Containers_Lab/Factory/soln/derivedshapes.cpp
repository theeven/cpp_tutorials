#include <iostream>
#include <memory>
#include "shape.h"
#include "factory.h"

// Note that knowlege of these individual derived classes and their
// creation functions is restricted to this .cpp file.  There is no
// coupling to these derived classes anywhere.
//
// Note that the individual derived Shapes would typically be in
// separate files in order to allow an implementer to select any
// subset for a partiuclar application.
//
// Each derived type registers itself with the shape factory during
// runtime static initialization.  The ShapeFactory Singleton
// implementation ensures that the ShapeFactory is initialized before
// use.

class Circle : public Shape {
  public:
	void draw() const { std::cout << "Circle" << std::endl; }
};
std::auto_ptr<Shape> makeCircle()
	{ return std::auto_ptr<Shape>(new Circle); }
const bool circleRegistered = ShapeFactory::instance().reg( "circle", makeCircle );

class Square : public Shape {
	void draw() const { std::cout << "Square" << std::endl; }
};
std::auto_ptr<Shape> makeSquare()
	{ return std::auto_ptr<Shape>(new Square); }
const bool squareRegistered = ShapeFactory::instance().reg( "square", makeSquare );

class Triangle : public Shape {
	void draw() const { std::cout << "Triangle" << std::endl; }
};
std::auto_ptr<Shape> makeTriangle()
	{ return std::auto_ptr<Shape>(new Triangle); }
const bool triangleRegistered = ShapeFactory::instance().reg( "triangle", makeTriangle );
