#include <iostream>
#include <vector>
#include "x.h"
#include "timer.h"

int main() {
	// See x.h
	using namespace std;

	try {
		typedef string value_type;
		const value_type value( "Hello!" );
		typedef X<value_type> XT;
		const XT::value_type temp( value );
		
		for( int reserve = 0; reserve < 2; ++reserve ) {
			XT::clearStats();
			{
				const int VECSIZE = 2000000;
				vector<XT> x;
				Timer t;
				if( reserve )
					x.reserve( VECSIZE );
				for( int i = 0; i < VECSIZE; ++i )
					x.push_back( temp );
				cout << "\tvector copy of size " << VECSIZE 
					<< (reserve ? " with" : " without") << " reserve"
					<< " took " << t << " seconds." << endl;
			}
			XT::printStats();
		}
		
		{
			const int VECSIZE = 10000000;
			vector<int> x( VECSIZE );
			Timer t1;
			for( int i = 0; i < VECSIZE; ++i )
				x[i] = 12345;
			cout << "[] of vector " << VECSIZE << " times took " << t1 << " seconds." << endl;

			Timer t2;
			for( int j = 0; j < VECSIZE; ++j )
				x.at( j ) = 12345;
			cout << "at() of vector " << VECSIZE << " times took " << t2 << " seconds." << endl;
		}
	}
	catch( bad_alloc & ) {
		cout << "out of memory!!!!!!!" << endl;
	}
	catch( ... ) {
		cout << "some other exception..." << endl;
	}

	return 0;
}
