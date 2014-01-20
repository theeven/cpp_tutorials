#ifndef STAB_H
#define STAB_H

#include <map>
#include <string>

struct Info {
	Info( int v = 0 ) : value(v) {}
    int value;
};

class Stab {
  public:
    bool insert( const std::string &id, const Info & );
    Info *lookup( const std::string &id );
  private:
    typedef std::map<std::string,Info> Tab;
    Tab tab;
};

bool Stab::insert( const std::string &id, const Info &info ) {
    return tab.insert( make_pair( id, info ) ).second;
}

Info *Stab::lookup( const std::string &id ) {
    Tab::iterator i( tab.find( id ) );
    if( i == tab.end() )
        return 0;
    else
        return &i->second;
}

#endif
