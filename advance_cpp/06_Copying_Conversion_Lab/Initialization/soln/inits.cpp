class X {
  public:
	X( int ) {}
	~X() {}
	X( const X & ) {}
	X &operator =( const X & ) { return *this; }
};

void func1( X ) {}
void func2( const X & ) {}
X func3() {
	X a( 12 ); // direct init
	return a; // copy init of return value
	// Note: application of NRV is likely here; result will
	// be functionally same as direct init of return value.
}
int func4() { return 12; }

void inits() {
	X a( 12 ); // direct init
	X b = 12; // copy init
	func1( 12 ); // copy init of formal argument
	func2( a ); // no copy: direct initialization of a temporary X, and binding a reference
	a = b; // copy assignment
	a = 12; // implicit conversion: direct init of temp, assignment, destruction of temp
	a = X(12); // explicit conversion: same result
	X c = func3(); // copy initialization of c
	X d( func3() ); // copy initialization of d
	a = func3(); // copy init of temporary and assignment to a
	X e = func4(); // copy initialization of e
	X f( func4() ); // direct initialization of f
}
