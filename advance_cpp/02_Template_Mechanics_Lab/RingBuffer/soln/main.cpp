#include <iostream>
#include "ringbuffer.h"
#include "tringbuffer.h"

int main() {
	using namespace std;
	
	RingBuffer b1;
	TRingBuffer<char,12> b2;
	TRingBuffer<char> b3;
	TRingBuffer<int> b4;
	
	for( const char *s = "Hello to all of you!"; *s; s++ ) {
		b1.push_back(*s);
		b2.push_back(*s);
		b3.push_back(*s);
		b4.push_back(*s);
	}
	while( !b1.empty() ) {
		cout << b1.front();
		b1.pop_front();
	}
	cout << endl;
	while( !b2.empty() ) {
		cout << b2.front();
		b2.pop_front();
	}
	cout << endl;
	while( !b3.empty() ) {
		cout << b3.front();
		b3.pop_front();
	}
	cout << endl;
	while( !b4.empty() ) {
		cout << b4.front() << ' ';
		b4.pop_front();
	}
	cout << endl;
	
	return 0;
}
