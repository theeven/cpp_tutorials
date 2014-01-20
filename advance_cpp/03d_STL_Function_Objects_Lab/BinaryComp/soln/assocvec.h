#ifndef ASSOCVEC_H
#define ASSOCVEC_H

#include <vector>
#include <algorithm>
#include <functional>

template <typename T, typename Comp = std::less<T> >
class AssocVec {
  public:
	typedef T value_type;
	typedef typename std::vector<T>::iterator iterator;
	typedef std::pair<iterator,bool> InsertRet;
	AssocVec( Comp comp = Comp() ) : comp_(comp) {}
	template <typename In>
	AssocVec( In b, In e );
	~AssocVec() {}
	// AssocVec( const AssocVec & );
	// AssocVec &operator =( const AssocVec & );
	iterator begin();
	iterator end();
	InsertRet insert( const T & );
	iterator find( const T & );
  private:
	std::vector<T> v_;
	Comp comp_;
	bool equiv( const T &a, const T &b )
		{ return !comp_(a,b) && !comp_(b,a); }
	struct Equiv {
		Equiv( AssocVec &av )
			: av_(av) {}
		bool operator ()( const T &a, const T &b ) const
			{ return !av_.comp_(a,b) && !av_.comp_(b,a); }
		AssocVec &av_;
	};
	friend class Equiv;
};

template <typename T, typename Comp>
template <typename In>
AssocVec<T,Comp>::AssocVec( In b, In e ) : v_( b, e ) {
	std::sort( v_.begin(), v_.end(), comp_ ); // Now sort with comparitor...
	v_.erase( std::unique( v_.begin(), v_.end(), Equiv(*this) ), v_.end() ); // ...and eliminate duplicates using equivalence.
}

template <typename T, typename Comp>
inline typename AssocVec<T,Comp>::iterator AssocVec<T,Comp>::begin()
	{ return v_.begin(); }

template <typename T, typename Comp>
inline typename AssocVec<T,Comp>::iterator AssocVec<T,Comp>::end()
	{ return v_.end(); }

template <typename T, typename Comp>
typename AssocVec<T,Comp>::iterator AssocVec<T,Comp>::find( const T &val ) {
	std::pair<iterator,iterator> result = std::equal_range( v_.begin(), v_.end(), val, comp_ );
	if( result.first == result.second )
		return end();
	else
		return result.first;
}

template <typename T, typename Comp>
typename AssocVec<T,Comp>::InsertRet AssocVec<T,Comp>::insert( const T &val ) {
	iterator result = std::lower_bound( v_.begin(), v_.end(), val, comp_ );
	if( result != v_.end() && equiv(*result,val) ) // use equivalence here, too
		return InsertRet(result,false);
	else
		return InsertRet(v_.insert( result, val ),true);
}

#endif
