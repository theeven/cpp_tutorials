#ifndef BINTREE_H
#define BINTREE_H

#include <functional>

//
//	BinaryTree is a simple, non-STL-compliant container that
//	implements a binary tree.
//
//	Like the STL associative containers, BinaryTree requires a
//	comparitor and uses equivalence rather than equality to
//	determine if an element is present in the tree.
//
//	There are two find functions available.  They both perform
//	the usual recursive tree traversal to look up a value.  "find"
//	returns the usual way from a (potentially) deeply nested
//	recursion.  "efind" throws an exception object that contains
//	the result.
//

template <typename T, typename Comp = std::less<T> >
class BinaryTree {
  public:
	BinaryTree();
	BinaryTree( Comp comp );
	~BinaryTree();
	bool insert( const T & );
	const T *find( const T & ) const;
	const T *efind( const T & ) const;
	struct Result {
		Result( const T *t ) : t_(t) {}
		Result() : t_(0) {}
		const T *t_;
	};
  private:
	struct Node {
		Node( const T &t ) : t_(t), l_(0), r_(0) {}
		~Node() { delete r_; delete l_; }
		bool insert( const T &, Comp );
		const T *find( const T &, Comp ) const;
		void efind( const T &, Comp ) const;
		T t_;
		Node *l_, *r_;
	} *root_;
	
	Comp comp_; // comparitor
	
	BinaryTree( const BinaryTree & );
	BinaryTree &operator =( const BinaryTree & );
};

template <typename T, typename Comp>
BinaryTree<T, Comp>::BinaryTree()
	: root_(0) {}

template <typename T, typename Comp>
BinaryTree<T, Comp>::BinaryTree( Comp comp )
	: root_(0), comp_(comp) {}

template <typename T, typename Comp>
BinaryTree<T, Comp>::~BinaryTree()
	{ delete root_; }

template <typename T, typename Comp>
bool BinaryTree<T, Comp>::insert( const T &t ) {
	if( root_ )
		return root_->insert( t, comp_ );
	else {
		root_ = new Node( t );
		return true;
	}
}

template <typename T, typename Comp>
bool BinaryTree<T, Comp>::Node::insert( const T &t, Comp comp ) {
	if( comp(t, t_) ) {
		if( l_ )
			l_->insert( t, comp );
		else
			l_ = new Node( t );
	}
	else if( comp(t_, t) ) {
		if( r_ )
			r_->insert( t, comp );
		else
			r_ = new Node( t );
	}
	return false; // already present
}

template <typename T, typename Comp>
const T *BinaryTree<T, Comp>::find( const T &t ) const {
	if( root_ )
		return root_->find( t, comp_ );
	else
		return 0;
}

template <typename T, typename Comp>
const T *BinaryTree<T, Comp>::Node::find( const T &t, Comp comp ) const {
	if( comp(t, t_) )
		return l_ ? l_->find( t, comp ) : 0;
	else if( comp(t_, t) )
		return r_ ? r_->find( t, comp ) : 0;
	else
		return &t; // success; found an equivalent
}

template <typename T, typename Comp>
const T *BinaryTree<T, Comp>::efind( const T &t ) const {
	if( root_ ) {
		try {
			root_->efind( t, comp_ );
		}
		catch( Result &f ) {
			return f.t_;
		}
	}
	return 0;
}

template <typename T, typename Comp>
void BinaryTree<T, Comp>::Node::efind( const T &t, Comp comp ) const {
	if( comp(t, t_) ) {
		if( l_ )
			l_->efind( t, comp );
		else
			throw Result();
	}
	else if( comp(t_, t) ) {
		if( r_ )
			r_->efind( t, comp );
		else
			throw Result();
	}
	else
		throw Result( &t_ );
}

#endif
