#include <iostream>
#include "factory.h"
#include "shape.h"

int main() {
	using namespace std;
	
	typedef auto_ptr<Shape> S;
	ShapeFactory &f = ShapeFactory::instance();
	
	try {
		S s1 = f.create( "circle" );
		S s2 = f.create( "square" );
		S s3 = f.create( "triangle" );
		
		s1->draw();
		s2->draw();
		s3->draw();
		
		S s4 = f.create( "blob" );
		s4->draw();
	}
	catch( std::exception &e ) {
		cout << "An exception! " << e.what() << endl;
	}
	
	return 0;
}
