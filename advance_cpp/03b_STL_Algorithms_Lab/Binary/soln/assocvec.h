#ifndef ASSOCVEC_H
#define ASSOCVEC_H

#include <vector>
#include <algorithm>

template <typename T>
class AssocVec {
  public:
	typedef T value_type;
	typedef typename std::vector<T>::iterator iterator;
	typedef std::pair<iterator,bool> InsertRet;
	AssocVec() {}
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
};

template <typename T>
template <typename In>
AssocVec<T>::AssocVec( In b, In e ) : v_( b, e ) {
	std::sort( v_.begin(), v_.end() ); // Note: sort using < operator...
	v_.erase( std::unique( v_.begin(), v_.end() ), v_.end() ); // ...but eliminate duplicates using equality!
}

template <typename T>
inline typename AssocVec<T>::iterator AssocVec<T>::begin()
	{ return v_.begin(); }

template <typename T>
inline typename AssocVec<T>::iterator AssocVec<T>::end()
	{ return v_.end(); }

template <typename T>
typename AssocVec<T>::iterator AssocVec<T>::find( const T &val ) {
	std::pair<iterator,iterator> result = std::equal_range( v_.begin(), v_.end(), val );
	if( result.first == result.second )
		return end();
	else
		return result.first;
}

template <typename T>
typename AssocVec<T>::InsertRet AssocVec<T>::insert( const T &val ) {
	iterator result = std::lower_bound( v_.begin(), v_.end(), val );
	if( result != v_.end() && !(*result < val ) && !(val < *result) ) // ...and here we're using equivalence!
		return InsertRet(result,false);
	else
		return InsertRet(v_.insert( result, val ),true);
}

#endif
