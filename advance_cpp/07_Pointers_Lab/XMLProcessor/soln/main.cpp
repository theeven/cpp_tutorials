#include "xmlprocessor.h"
#include "xmlprocessor_smart.h"


int main() {
	using namespace std;
	
	//XMLProcessor a; // undefined behavior!
	XMLProcessorAuto b;
	XMLProcessorShared c;
	
	return 0;
}

