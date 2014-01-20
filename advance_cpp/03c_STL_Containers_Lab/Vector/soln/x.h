#ifndef X_H
#define X_H

#include <iostream>

template<class T>
class X {
public:
	X( const T &a ) : _data( a ) { ++_nondefault; }
	X() { ++_default; }
	~X() { ++_destructor; }
	X( const X &that ) : _data( that._data ) { ++_copy; }
	X &operator =( const X &rhs ) { _data = rhs._data; ++_assign; return *this; }
	operator T &() { return _data; }
	operator const T &() const { return _data; }
	static void printStats();
	static void clearStats();
	typedef T value_type;
private:
	T _data;
	static long _nondefault;
	static long _default;
	static long _destructor;
	static long _copy;
	static long _assign;
};

template <class T> long X<T>::_nondefault = 0;
template <class T> long X<T>::_default = 0;
template <class T> long X<T>::_destructor = 0;
template <class T> long X<T>::_copy = 0;
template <class T> long X<T>::_assign = 0;

template <class T>
void X<T>::printStats() {
	using std::cout;
	using std::endl;

	cout << "***  X Statistics  ***" << endl;
	cout << "\tOne-arg ctor:\t" << _nondefault << endl;
	cout << "\tDefault ctor:\t" << _default << endl;
	cout << "\tDestructor:\t" << _destructor << endl;
	cout << "\tCopy ctor:\t" << _copy << endl;
	cout << "\tAssignments:\t" << _assign << endl << endl;
}

template <class T>
void X<T>::clearStats() {
	_nondefault = 0;
	_default = 0;
	_destructor = 0;
	_copy = 0;
	_assign = 0;
}

#endif
