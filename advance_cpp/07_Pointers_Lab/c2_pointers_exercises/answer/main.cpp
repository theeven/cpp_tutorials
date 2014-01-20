#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include <list>

#include "xmlprocessor.h"
#include "xmlprocessor_smart.h"
#include "cptr_inst.h"
#include "shapes.h"

////////////////
//	Exercise #6
//

void exercise6() {
	// See cptr_inst.h
	using namespace std;
	cout << "\n===  EXERCISE #6  ===" << endl;
	
	vector< Cptr<Shape> > pic;
	pic.push_back( new Circle );
	pic.push_back( new Triangle );
	pic.push_back( new Square );
	
	list< Cptr<Shape> > picture;
	picture.push_back( pic[2] );
	picture.push_back( new Triangle );
	picture.push_back( pic[0] );
	
	pic[0] = pic[1];
	picture.back() = pic[1];
	picture.front() = picture.back();
	picture.front() = pic[0];
}

////////////////
//	Exercise #7
//

std::string *source()
	{ return new std::string( "Hello!" ); }

void sink( std::string *a, std::string *b, std::string *c ) {
    std::cout << *a << *b << *c;
    delete a;
    delete b;
    delete c;
}

void f() {
    sink( source(), new std::string( "..." ), source() );
}

std::auto_ptr<std::string> source2()
	{ return std::auto_ptr<std::string>(new std::string( "Hello!" )); }

void sink2( std::auto_ptr<std::string> a, std::auto_ptr<std::string> b, std::auto_ptr<std::string> c ) {
    std::cout << *a << *b << *c;
}

void f2() {
    sink( source(), new std::string( "..." ), source() );
}

void exercise7() {
	using namespace std;
	cout << "\n===  EXERCISE #7  ===" << endl;
	
	f();
	f2();
}

////////////////
//	Exercise #8
//

void exercise8() {
	// See xmlprocessor.h and xmlprocessor_smart.h
	using namespace std;
	cout << "\n===  EXERCISE #8  ===" << endl;
	
	//XMLProcessor a; // undefined behavior!
	XMLProcessorAuto b;
	XMLProcessorShared c;
}

int main() {
	exercise6();
	exercise7();
	exercise8();
	
	return 0;
}
