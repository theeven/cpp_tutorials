#include <iostream>
#include <vector>
#include <list>

#include "cptr_inst.h"
#include "shapes.h"
	
int main() {
	using namespace std;
		
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
	
	return 0;
}
