#ifndef FACTORY_H
#define FACTORY_H

#include <string>
#include <stdexcept>
#include <map>
#include <memory>

class Shape;

// A simple factory that maps an identifier of type string to a
// function that generates an object of the corresponding type.
// The factory contains function to register an id/function pair,
// unregister an id, and create an object from an id.

class ShapeFactory {
  public:
	typedef std::auto_ptr<Shape>(*Generator)();
	bool reg( const std::string &shapeId, Generator shapeGenerator );
	bool unreg( const std::string &shapeId );
	std::auto_ptr<Shape> create( const std::string &shapeId ) const;
	static ShapeFactory &instance(); // Singleton
  private:
	ShapeFactory() {}
	typedef std::map<std::string,Generator> Map;
	Map impl_;
};

class BadShapeId : public std::runtime_error {
  public:
	BadShapeId( const std::string &id ) : std::runtime_error( "Bad Shape id: "+id ) {}
};

inline bool ShapeFactory::reg( const std::string &id, Generator gen )
	{ return impl_.insert( Map::value_type(id,gen)).second; }

inline bool ShapeFactory::unreg( const std::string &id )
	{ return impl_.erase(id) == 1; }

// These two functions should proably not be inline, but...
inline std::auto_ptr<Shape> ShapeFactory::create( const std::string &id ) const {
	Map::const_iterator i = impl_.find(id);
	if( i == impl_.end() )
		throw BadShapeId( id );
	return (i->second)();
}

inline ShapeFactory &ShapeFactory::instance() { // Meyers Singleton implementation
	static ShapeFactory theFactory;
	return theFactory;
}

#endif
