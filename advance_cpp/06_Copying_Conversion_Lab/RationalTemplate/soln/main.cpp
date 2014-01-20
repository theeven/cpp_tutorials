#include <iostream>
#include "trational.h"

struct MyInt { // for use with rational number template
  public:
	MyInt( int v = 0 ) : v_(v) {}
	MyInt &operator *=( const MyInt &rhs )
		{ v_ *= rhs.v_; return *this; }
	MyInt &operator /=( const MyInt &rhs )
		{ v_ / rhs.v_; return *this; }
	MyInt &operator %=( const MyInt &rhs )
		{ v_ % rhs.v_; return *this; }
	MyInt &operator +=( const MyInt &rhs )
		{ v_ += rhs.v_; return *this; }
	MyInt &operator -=( const MyInt &rhs )
		{ v_ -= rhs.v_ ; return *this; }
	MyInt &operator -()
		{ v_ = -v_ ; return *this; }
	friend MyInt operator *( const MyInt &lhs, const MyInt &rhs )
		{ return MyInt( lhs.v_ * rhs.v_ ); }
	friend MyInt operator /( const MyInt &lhs, const MyInt &rhs )
		{ return MyInt( lhs.v_ / rhs.v_ ); }
	friend MyInt operator %( const MyInt &lhs, const MyInt &rhs )
		{ return MyInt( lhs.v_ % rhs.v_ ); }
	friend MyInt operator +( const MyInt &lhs, const MyInt &rhs )
		{ return MyInt( lhs.v_ + rhs.v_ ); }
	friend MyInt operator -( const MyInt &lhs, const MyInt &rhs )
		{ return MyInt( lhs.v_ - rhs.v_ ); }
	friend bool operator ==( const MyInt &a, const MyInt &b )
		{ return a.v_ == b.v_; }
	friend bool operator !=( const MyInt &a, const MyInt &b )
		{ return !(a == b); }
	friend bool operator <( const MyInt &a, const MyInt &b )
		{ return a.v_ < b.v_; }
	friend bool operator >=( const MyInt &a, const MyInt &b )
		{ return !(a < b); }
	friend std::ostream &operator <<( std::ostream &os, const MyInt &i )
		{ return os << i.v_; }
  private:
	int v_;
};

int main() {	
	using namespace std;
	
	{
	R<short> x(1,2), y(2,3), z;
	cout << x << " * " << y << " == " << (z = x*y) << endl;
	}
	{
	R<int> x(1,2), y(2,3), z;
	cout << x << " * " << y << " == " << (z = x*y) << endl;
	}
	{
	R<long> x(1,2), y(2,3), z;
	cout << x << " * " << y << " == " << (z = x*y) << endl;
	}
	{
	R<MyInt> x(1,2), y(2,3), z;
	cout << x << " * " << y << " == " << (z = x*y) << endl;
	}
	{
	R<MyInt> x(1,2), y(2,3), z;
	cout << x << " + " << y << " == " << (z = x+y) << endl;
	}
	{
	R<bool> x(1,2), y(2,3), z;
	cout << x << " + " << y << " == " << (z = x+y) << endl;
	}
	{
	R<char> x(1,2), y(2,3), z;
	cout << x << " + " << y << " == " << (z = x+y) << endl;
	}
	{
	R<int> c;
	cout << "Enter a rational number of the form a/b: " << flush;
	cin >> c;
	cout << "That was a " << c << endl;
	}
		
	return 0;
}
