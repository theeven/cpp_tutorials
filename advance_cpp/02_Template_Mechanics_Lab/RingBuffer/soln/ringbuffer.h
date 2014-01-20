#ifndef RINGBUFFER_H
#define RINGBUFFER_H

// Note:  Original version of ring_buffer.h by Dan Saks.
// This version has been hacked by S. C. Dewhurst.

class RingBuffer {
  public:
	RingBuffer();
	bool empty() const;
	char front() const;
	void pop_front();
	void push_back( char c );
  private:
	enum { size = 32 };
	char buffer_[size];
	unsigned int head_, tail_;
};

inline
RingBuffer::RingBuffer():
	head_(0), tail_(0) {}

inline
bool RingBuffer::empty() const
	{ return head_ == tail_; }

inline
char RingBuffer::front() const
	{ return buffer_[head_]; }

inline
void RingBuffer::pop_front() {
	if( ++head_ >= size )
		head_ = 0;
}

#endif
