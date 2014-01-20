#include "stack.h"
#include <string>

int main() {
	Stack<int> s1;
	s1.push( 12 );
	s1.push( 10 );
	if( !s1.isEmpty() )
		s1.pop();
	
	Stack<std::string> s2;
	s2.push( "Hello" );
	s2.push( "World" );
	if( !s2.isEmpty() )
		s2.pop();
	
	return 0;
}
