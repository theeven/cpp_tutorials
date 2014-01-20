#ifndef TRINGBUFFER_H
#define TRINGBUFFER_H

template <typename T, unsigned int size = 32>
class TRingBuffer {
  public:
	TRingBuffer();
	bool empty() const;
	T front() const;
	void pop_front();
	void push_back( const T &);
  private:
	T buffer_[size];
	unsigned int head_, tail_;
};

template <typename T, unsigned int size>
inline TRingBuffer<T,size>::TRingBuffer():
	head_(0), tail_(0) {}

template <typename T, unsigned int size>
inline bool TRingBuffer<T,size>::empty() const
	{ return head_ == tail_; }

template <typename T, unsigned int size>
inline T TRingBuffer<T,size>::front() const
	{ return buffer_[head_]; }

template <typename T, unsigned int size>
inline void TRingBuffer<T,size>::pop_front() {
	if( ++head_ >= size )
		head_ = 0;
}

template <typename T, unsigned int size>
void TRingBuffer<T,size>::push_back( const T &c ) {
	unsigned int new_tail = tail_;
	if( ++new_tail >= size )
		new_tail = 0;
	if( new_tail != head_ ) {
		buffer_[tail_] = c;
		tail_ = new_tail;
	}
}

#endif
