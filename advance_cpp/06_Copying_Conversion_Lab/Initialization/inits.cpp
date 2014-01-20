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
	X a( 12 ); // ???
	return a; // ???
}
int func4() { return 12; }

void inits() {
	X a( 12 ); // ???
	X b = 12; // ???
	func1( 12 ); // ???
	func2( a ); // ???
	a = b; // ???
	a = 12; // ???
	a = X(12); // ???
	X c = func3(); // ???
	X d( func3() ); // ???
	a = func3(); // ???
	X e = func4(); // ???
	X f( func4() ); // ???
}
