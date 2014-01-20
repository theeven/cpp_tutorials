#include <iostream>
#include "register.h"
#include "vregister.h"

////////////////
//	PART #1
//

namespace {
	char buf[sizeof(Register)];
	unsigned rloc[2];
}

void part1() {
	// See implementation in register.h
	using namespace std;
	cout << "\n===  PART #1  ===" << endl;
	
	// Using placement new to allocate the register at a
	// particular address.
	Register *r = new (buf) Register;
	//...
	r->~Register();
}

////////////////
//	Part #2
//

void part2() {
	// See implementations in vregister.h
	using namespace std;
	cout << "\n===  PART #2  ===" << endl;
	
	StdRegister r2( buf );
	CacheRegister r3( buf );
	r3.write( 12 );
	cout << r3.lastWrite() << endl;
	cout << r3.read() << endl;
	cout << r3.lastRead() << endl;
	MonoReg<int,&rloc> r4;
	MonoReg<char,buf> r7;
	r4.write( 12 );
	r7.write( 12 );
	
	VReg *r5 = new StdReg( buf );
	r5 = new BlabDecorator( r5 );
	r5->write( 12 );
	r5 = new AugmentDecorator( r5, -3 );
	r5->write( 12 );
	auto_ptr<CacheDecorator> r6( new CacheDecorator( r5 ) );
	r6->write( 12 );
	cout << r6->lastWrite() << endl;
}

int main() {
	part1();
	part2();
	
	return 0;
}