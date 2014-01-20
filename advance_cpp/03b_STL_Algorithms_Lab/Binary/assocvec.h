#ifndef ASSOCVEC_H
#define ASSOCVEC_H

#include <vector>
#include <algorithm>

template <typename T>
class AssocVec {
  public:
	typedef T value_type;
	typedef std::vector<T>::iterator iterator;
	AssocVec() {}
	template <typename In>
	AssocVec( In b, In e );
	~AssocVec() {}
	// AssocVec( const AssocVec & );
	// AssocVec &operator =( const AssocVec & );
	iterator begin();
	iterator end();
	iterator insert( const T & );
	iterator find( const T & );
  private:
	std::vector<T> v_;
};

template <typename T>
template <typename In>
AssocVec<T>::AssocVec( In b, In e ) : v_( b, e ) {
	// TO DO...
}

template <typename T>
inline typename AssocVec<T>::iterator AssocVec<T>::begin() {
	//TO DO...
}

template <typename T>
inline typename AssocVec<T>::iterator AssocVec<T>::end() {
	// TO DO...
}

template <typename T>
typename AssocVec<T>::iterator AssocVec<T>::find( const T &val ) {
	// TO DO...
}

template <typename T>
typename AssocVec<T>::iterator AssocVec<T>::insert( const T &val ) {
	// TO DO...
}

#endif
