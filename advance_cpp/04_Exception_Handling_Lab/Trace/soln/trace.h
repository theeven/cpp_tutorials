#ifndef TRACE_H
#define TRACE_H

#include <iostream>
#include <string>
#include <exception>

#define MW

class Trace {
  public:
	Trace( const char *msg )
		: msg_(msg) {
		std::cout << "Entering " << msg_ << std::endl;
	}
	~Trace() {
		std::cout << "Leaving " << msg_;
#ifndef MW
		if( std::uncaught_exception() )
			std::cout << " due to an exception.";
#endif
		std::cout << std::endl;
	}
  private:
	std::string msg_;
};

#endif
