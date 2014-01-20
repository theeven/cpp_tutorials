#include <iostream>
#include <numeric>
#include <cassert>
#include "zeroout.h"

int main() {
	// See zeroout.h
	using namespace std;
		
	const int hrsinweek = 7*24;
	float readings[hrsinweek];
	zeroOut( readings ); // bound == 168, T is float
	int sum1 = accumulate( readings, readings+hrsinweek, 0 );
	assert( sum1 == 0 );
	
	float monthlyAverages[] = {1,2,3,4,5,6,7,8,9,10,11,12};
	const int months = sizeof(monthlyAverages)/sizeof(monthlyAverages[0]);
	zeroOut( monthlyAverages ); // bound == 12, T is float
	float sum2 = accumulate( monthlyAverages, monthlyAverages+months, 0 );
	assert( sum2 == 0 );
	
	float *fp = monthlyAverages;
	monthlyAverages[2] = 123.45;
	zeroOut( fp, months ); // use 2-arg version for pointer
	float sum3 = accumulate( fp, fp+months, 0 );
	assert( sum3 == 0 );
	
	cout << "Succeeded!" << endl;
		
	return 0;
}
