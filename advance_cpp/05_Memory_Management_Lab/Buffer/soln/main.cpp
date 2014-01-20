#include <iostream>
#include <vector>
#include "allocandinit.h"

int main() {
	// See allocandinit.h
	using namespace std;
	cout << "\n===  EXERCISE  ===" << endl;
	
	char alpha[] = "abcdefghijklmnopqrstuvwxyz";
	const int alphalen = sizeof(alpha)/sizeof(alpha[0]);
	vector<char> alphv( alpha, alpha+alphalen );
	int *ibuf1 = allocAndInit<int>( alphalen, alpha, alpha+alphalen );
	int *ibuf2 = allocAndInit<int>( alphv.size(), alphv.begin(), alphv.end() );
	delete [] ibuf2;
	delete [] ibuf1;

	return 0;
}
