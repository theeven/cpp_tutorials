class X {
  public:
	X( int ) {}
	~X() {}
  private:
	X( const X & );
	X &operator =( const X & );
};

void func1( X ) {}
void func2( const X & ) {}
X func3() {
	X a( 12 ); // direct init
	return a; // ==>ERROR: copy init of return value
	// Note: application of NRV is likely here; result will
	// be functionally same as direct init of return value.
}
int func4() { return 12; }

void inits() {
	X a( 12 ); // direct init
	X b = 12; // copy init
	func1( 12 ); // ==>ERROR (often not diagnosed by comiler): copy init of formal argument
	func2( a ); // no copy: direct initialization of a temporary X, and binding a reference
	a = b; // ==>ERROR: copy assignment
	a = 12; // ==>ERROR: implicit conversion: direct init of temp, assignment, destruction of temp
	a = X(12); // ==>ERROR: explicit conversion: same result
	X c = func3(); // ==>ERROR: copy initialization of c
	X d( func3() ); // ==>ERROR: copy initialization of d
	a = func3(); // ==>ERROR: copy init of temporary and assignment to a
	X e = func4(); // ==>ERROR (often not diagnosed by compiler): copy initialization of e
	X f( func4() ); // direct initialization of f
}
