#include "ringbuffer.h"

void RingBuffer::push_back( char c ) {
	unsigned int new_tail = tail_;
	if( ++new_tail >= size )
		new_tail = 0;
	if( new_tail != head_ ) {
		buffer_[tail_] = c;
		tail_ = new_tail;
	}
}

