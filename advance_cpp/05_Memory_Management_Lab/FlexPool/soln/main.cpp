#include <iostream>
#include "flexpool.h"

class X2 {
  public:
	X2() : x_(1) {}
	virtual ~X2() {}
	
	// We can allow classes derived from X to inherit the allocation
	// operations that use FlexPool, since the size of the request
	// may be specified at runtime to FlexPool.
	void *operator new( std::size_t n )
		{ return pool_.alloc( n ); }
	// Note that we use the two-argument form of operator delete (and
	// ensure that X2 has a virtual dtor) so that FlexPool's free
	// operation knows the size of what's being deleted.
	void operator delete( void *p, std::size_t n )
		{ pool_.free( p, n ); }
	
	// Unlike the case with FixedPool, FlexPool allows runtime specification
	// of the allocation size, and so may be used to implement array allocation
	// operations.  This may still not be a good idea, since FlexPool is not
	// very good at reusing odd sizes of memory.
	void *operator new[] ( std::size_t n )
		{ return pool_.alloc( n ); }
	void operator delete []( void *p, std::size_t n )
		{ pool_.free( p, n ); }
  private:
	int x_;
	// Note that this FlexPool will be used for all classes derived from X2,
	// but not for others.
	static FlexPool<> pool_;
};

FlexPool<> X2::pool_;

class Y2 : public X2 {
  public:
	Y2() : y_(2) {}
  private:
	int y_;
};

int main() {
	using namespace std;
	cout << "\n===  EXERCISE  ===" << endl;
	
	auto_ptr<X2> xp1( new X2 );
	auto_ptr<X2> xp2( new Y2 );
	auto_ptr<Y2> yp1( new Y2 );
	X2 *xap = new Y2[12];
	delete [] xap;	
	return 0;
}
