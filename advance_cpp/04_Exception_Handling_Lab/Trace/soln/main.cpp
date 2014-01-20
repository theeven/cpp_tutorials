#include <iostream>
#include "trace.h"

Trace a( "global" );

void function() {
	using namespace std;
	
	bool flag = true;
	Trace a( "function" );
	label: Trace b( "after label" );
	if( flag ) {
		Trace a( "if" );
		flag = false;
		goto label;
	}
	else
		return;
}

class B1 {
  public:
	B1() : a( "Base class B1" ) {}
	Trace a;
};

class B2 {
  public:
	B2() : a( "Base class B2" ) {}
	Trace a;
};

class D : public B1, public B2 {
  public:
	D() : member1( "D::member1" ), member2( "D::member2" )
		{ Trace a( "D ctor body" ); }
	Trace member1;
	Trace member2;
	~D() { Trace a( "D dtor body" ); }
};

int main() {
	using namespace std;
	
	Trace a( "main" );
	D d;
	function();
	
	return 0;
}

Trace b( "more global" ); // for exercise #1
