#include <iostream>
#include "fixedpool.h"

///////////////////////
//	Parts #1 and #2
//

class X {
  public:
	X() : x_(1) {}
	virtual ~X() {}
	
	// Part #1
	void *operator new( std::size_t )
		{ return FixedPool<sizeof(X)>::alloc(); }
	void operator delete( void *p )
		{ FixedPool<sizeof(X)>::free( p ); }
	
	// Part #2
	// One option is not to implement memory management for
	// arrays.  That's pretty much what we've done below, but
	// we've made the decision explicit by defining zero-cost
	// forwarding functions.
	//
	// It would be difficult (or impossible?) to use FixedPool
	// to implement the array allocation because we don't know
	// at compile time how big each request will be, and the
	// FixedPool template requires a compile-time constant for
	// its instantiation.
	void *operator new[] ( std::size_t n )
		{ return ::operator new[]( n ); }
	void operator delete []( void *p )
		{ ::operator delete []( p ); }
  private:
	int x_;
};

void parts1and2() {
	using namespace std;
	cout << "\n===  PARTS #1 and #2  ===" << endl;
	
	X *xp1 = new X;
	X *xp2 = new X[12];
	auto_ptr<X> xp3;
	delete [] xp2;
	delete xp1;
}

////////////////
//	Part #3
//

class Y : public X {
  public:
	Y() : y_(2) {}
	
	// Exercise 3
	// Note that Y must define its own FixedPool allocator rather
	// inherit from its X base class.  If Y happened to have the
	// same size as X, they will both share the same allocator
	// implementation anyway.
	// Note that this sharing may not always be desirable, since
	// unrelated classes that happen to have the same size will
	// share the same FixedPool, and may negatively affect locality
	// of reference for objects of a particular type.
	void *operator new( std::size_t )
		{ return FixedPool<sizeof(Y)>::alloc(); }
	void operator delete( void *p )
		{ FixedPool<sizeof(Y)>::free( p ); }
  private:
	int y_;
};

void part3() {
	using namespace std;
	cout << "\n===  PART #3  ===" << endl;
	
	auto_ptr<X> xp1( new X );
	auto_ptr<X> xp2( new Y );
	auto_ptr<Y> yp1( new Y );
	X *xap = new Y[12];
	delete [] xap;
}

////////////////
//	Part #4
//
class BadX {
  public:
	BadX() : x_(1) {}
	~BadX() {} // Note: non-virtual dtor!
	
	void *operator new( std::size_t )
		{ return FixedPool<sizeof(X)>::alloc(); }
	void operator delete( void *p )
		{ FixedPool<sizeof(X)>::free( p ); }
  private:
	int x_;
};

class BadY : public BadX {
  public:
	BadY() : y_(2) {}
	void *operator new( std::size_t )
		{ return FixedPool<sizeof(Y)>::alloc(); }
	void operator delete( void *p )
		{ FixedPool<sizeof(Y)>::free( p ); }
  private:
	int y_;
};

void part4() {
	using namespace std;
	cout << "\n===  PART #4  ===" << endl;
	
	// The deletions below have undefined behavior.
	// The likely result is that the memory pool for
	// X will be corrupted (assuming sizeof(BadX) !=
	// sizeof(BadY)), but anything at all could
	// happen!
	auto_ptr<BadX> xp1( new BadX );
	auto_ptr<BadX> xp2( new BadY );
	auto_ptr<BadY> yp1( new BadY );
}

int main() {
	parts1and2();
	part3();
	part4();
	
	return 0;
}
