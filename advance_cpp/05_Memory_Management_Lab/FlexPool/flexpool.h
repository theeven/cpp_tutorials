#ifndef FLEXPOOL_H
#define FLEXPOOL_H

//
//	Quick and simple variable-sized memory pool implementation
//	for use in exercises.  This is not industrial-strength!
//	Consider instead the version(s) from boost.org or a
//	commercial product.
//

#include <new>
#include <cstdlib>

const int defaultFlexPoolBlockSize = 1000;

template <int blockSize = defaultFlexPoolBlockSize>
class FlexPool {
  public:
  	FlexPool() : start_( 0 ), end_( 0 ), free_( 0 ) {}
  	~FlexPool() {}
	void *alloc( std::size_t nbytes );
	void free( void *p, std::size_t nbytes );
  private:
  	static std::size_t requestSize( std::size_t n ) {
  		const std::size_t align = sizeof(double);  // not portable, but probably work...
  		const std::size_t unit = sizeof(Unit);
  		std::size_t tmp = n < unit ? unit : n;
  		std::size_t tmp2 = (tmp+align-1)/align;
  		return tmp2*align;
  	}
  	
	struct Unit {
		Unit *next_;
		std::size_t len_;
	};
	Unit *start_; // current pos in block
	Unit *end_; // one past end of block
	Unit *free_; // head of freelist
	
	FlexPool( const FlexPool & );
	FlexPool &operator =( const FlexPool & );
};

template <int s>
void *FlexPool<s>::alloc( std::size_t nbytes ) {
	if( nbytes == 0 )
		nbytes = 1;
	const std::size_t n = requestSize( nbytes );
	const std::size_t nunits = n/sizeof(Unit);
		
	if( n > s ) // request too big for block size
		return ::operator new( n );
		
	Unit *p = free_;
	Unit *q = p;
	while( p ) { // for each element on freelist
		if( p->len_ == n ) { // if this node fits request exactly
			if( p == free_ )
				free_ = free_->next_;
			else
				p->next_ = q->next_;
			return p;
		}
		q = p;
		p = p->next_;
	}
	if( end_ - start_ >= nunits ) { // if enough space left
		Unit *tmp = start_;
		start_ += nunits;
		return tmp;
	}
	// get new block and try again
	Unit *tmp = static_cast<Unit *>(::operator new( defaultFlexPoolBlockSize ));
	start_ = tmp;
	end_ = start_+(defaultFlexPoolBlockSize/sizeof(Unit));
	return alloc( nbytes );
}

template <int s>
void FlexPool<s>::free( void *p, std::size_t nbytes ) {
	const std::size_t n = requestSize( nbytes );

	if( n > s )
		return ::operator delete( p );
	
	static_cast<Unit *>(p)->next_ = free_;
	free_ = static_cast<Unit *>(p);
	free_->len_ = n;
}

#endif
