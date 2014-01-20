#include <iostream>
#include <boost/function.hpp>

void exercise1() {
	// original cast
	char *buffer = 0;
	int *ip = (int *) buffer;
	
	// with new cast
	ip = reinterpret_cast<int *>(buffer);
}

void exercise2() {
	// original cast
	const char *buffer;
	int *ip = (int *) buffer;

	// with new cast
	ip = reinterpret_cast<int *>(const_cast<char *>(buffer));
	// or...
	ip = const_cast<int *>(reinterpret_cast<const int *>(buffer));
}

class Shape {
  public:
	virtual ~Shape() {}
};
class Circle : public Shape {
};

void exercise3() {
	// original cast
	const Shape *exemplar = 0;
	Circle *ip = (Circle *) exemplar;
	
	const Circle *cip; // all the examples below require a const cast too...
	
	// with dynamic cast, check correctness at runtime
	cip = dynamic_cast<const Circle *>(exemplar);
	
	// with dynamic cast to reference, state an invariant
	dynamic_cast<const Circle &>(*exemplar);
	
	// with dynamic cast to void, find the address of the
	// complete object
	const void *start = dynamic_cast<const void *>(exemplar);
	
	// with static cast, hope for the best
	cip = static_cast<const Circle *>(exemplar);
	
	// with reinterpret cast, pretend the Shape addr is also
	// a Circle addr; probably not what you want
	cip = reinterpret_cast<const Circle *>(exemplar);
}

// Exercise 4
template <typename T>
class SP1 {
  public:
	explicit SP1( T *p ) : p_(p) {}
	~SP1() { delete p_; }
	T *operator ->() const { return p_; }
	T &operator *() const { return *p_; }
  private:
	T *p_;
	SP1( const SP1 & );
	SP1 &operator =( const SP1 & );
};

// Oops, mea culpa.
// Derived to base conversions don't make sense for a scoped pointer
// since they shouldn't support copying.  Here I've reinvented auto_ptr.

template <typename T>
class SP2 {
  public:
	explicit SP2( T *p ) : p_(p) {}
	~SP2() { delete p_; }
	T *operator ->() const { return p_; }
	T &operator *() const { return *p_; }
	SP2( SP2 &that )
		: p_(that.p_) { that.p_ = 0; }
	SP2 &operator =( SP2 &rhs )
		{ delete p_; p_ = rhs.p_; rhs.p_ = 0; return *this; }
	template <typename S>
	SP2( SP2<S> &that )
		: p_(that.get()) { that.get() = 0; }
	template <typename S>
	SP2 &operator =( SP2<S> &rhs )
		{ delete p_; p_ = rhs.get(); rhs.get() = 0; return *this; }
	T *&get()
		{ return p_; }
  private:
	// friend decl below should work, but doesn't on some compilers,
	// so I added the get function to implement member templates above.
	// There is, no doubt, a better solution.
	// template <typename S> friend class SP2;
	T *p_;
};

void exercise4() {
	SP1<int> p1( new int(12) );
	SP2<Circle> p2( new Circle );
	//SP2<Shape> p3( p2 );
	SP2<Shape> p4( new Circle );
	p4 = p2;
}

// exercise 5
void someOtherFunction() {}
class X { public: X( int a ) : a_(a) {} int a_; };

// original
void someFunction() {
    X *xp = new X(12);
    someOtherFunction();
    delete xp;
}

// with scoped pointer
void someFunction2() {
    SP1<X> xp( new X(12) );
    someOtherFunction();
}

// without scoped pointer
void someFunction3() {
    X *xp = new X(12);
    try {
    	someOtherFunction();
    }
    catch( ... ) {
    	delete xp;
    	throw;
    }
    delete xp;
}

void exercise5() {
	someFunction();
	someFunction2();
	someFunction3();
}

// exercise 6
class Button {
  public:
    Button( const std::string &lab, void (*cb)() = 0 )
        : label_(lab), callback_(cb) {}
    ~Button() {}
    void setCallback( void (*cb)() )
        { callback_ = cb; }
    void click() const
        { if( callback_ ) callback_(); }
  private:
    std::string label_;
    void (*callback_)(); // action on click
};

void doNothing() { std::cout << "click:doNothing" << std::endl; }
int f2() { std::cout << "click:f2" << std::endl; return 12; }
struct F3 {
	double operator ()( int *p = 0 ) { std::cout << "click:F3" << std::endl; return 12.3+int(p); }
};

class Button2 {
  public:
    Button2( const std::string &lab, boost::function<void(void)> cb = doNothing )
        : label_(lab), callback_(cb) {}
    ~Button2() {}
    void setCallback( boost::function<void(void)> cb )
        { callback_ = cb; }
    void click() const
        { callback_(); }
  private:
    std::string label_;
    boost::function<void(void)> callback_; // action on click
};

void exercise6() {
	Button2 b1( "Button1" );
	b1.click();
	b1.setCallback( f2 );
	b1.click();
	b1.setCallback( F3() );
	b1.click();
}

int main() {
	exercise6();
	return 0;
}
