#include <string>
#include <memory>
#include <iostream>

using std::string;
using std::auto_ptr;
using std::cout;

// Original version with raw pointers.
//
string *source() {
	return new string( "Hello!" );
}

void sink( string *a, string *b, string *c ) {
    cout << *a << *b << *c;
    delete a;
    delete b;
    delete c;
}

void f() {
    sink( source(), new string( "..." ), source() );
}

// Version with auto_ptrs.
//
auto_ptr<std::string> source2()
	{ return auto_ptr<string>(new string( "Hello!" )); }

void sink2( auto_ptr<std::string> a, auto_ptr<string> b, auto_ptr<string> c ) {
    cout << *a << *b << *c;
}

void f2() {
    sink( source(), new string( "..." ), source() );
}

int main() {
	f();
	f2();
	
	return 0;
}
