#ifndef FIXEDPOOL_H
#define FIXEDPOOL_H

//
//	Quick and simple fixed-sized memory pool implementation
//	for use in exercises.  This is not industrial-strength!
//	Consider instead the version(s) from boost.org or a
//	commercial product.
//
//	Example 1: FixedPool<8>::alloc() will alloc 8 bytes from
//	the 8-byte memory pool.
//
//	Example 2: FixedPool<sizeof(Type)>::alloc() will alloc
//	sizeof(Type) bytes from the sizeof(Type)-byte memory pool.
//	FixedPool<sizeof(Type)>::free(ptr) will return the memory
//	for the object referred to by ptr to the sizeof(Type)-byte
//	memory pool.
//
//	Note:  The block size of each allocated segment can be set with
//	an optional second template argument.
//
//	Note:  pool sizes less than sizeof(pointer to data) will
//	actually consume sizeof(pointer to data) bytes per object.
//
//	Note:  A memory pool of a given size will exist only if
//	it is actually used.

#include <exception>
#include <cstdlib>

const int defaultFixedPoolBlockSize = 1000;

template <int n, int blockSize = defaultFixedPoolBlockSize>
class FixedPool {
  public:
	static void *alloc();
	static void free( void *p );
  private:
	union Unit {
		char store_[n];
		Unit *next_;
	};
	static Unit *block_; // current block
	static Unit *free_; // head of freelist
	static int num_used_; // number of slots used in current block
};

template <int n, int s>
typename FixedPool<n,s>::Unit *FixedPool<n,s>::free_ = 0;

template <int n, int s>
int FixedPool<n,s>::num_used_ = s;

template <int n, int s>
typename FixedPool<n,s>::Unit *FixedPool<n,s>::block_ = 0;

template <int n, int s>
void *FixedPool<n,s>::alloc() {
		if( free_ ) { // if something on freelist
			Unit *tmp = free_; // take from freelist
			free_ = free_->next_;
			return tmp;
		}
		else if( num_used_ < s ) // if slots left
			return &block_[ num_used_++ ]; // return unused slot
		else { // get new block and try again
			Unit *tmp = static_cast<Unit *>(std::malloc( sizeof(Unit)*s ));
			if( tmp ) {
				block_ = tmp;
				num_used_ = 0;
				return alloc();
			}
		}
		throw std::bad_alloc(); // otherwise, we're out of memory!
}

template <int n, int s>
void FixedPool<n,s>::free( void *p ) {
		static_cast<Unit *>(p)->next_ = free_;
		free_ = static_cast<Unit *>(p);
}

#endif
