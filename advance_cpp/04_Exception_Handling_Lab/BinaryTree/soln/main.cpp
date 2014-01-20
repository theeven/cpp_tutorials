#include <iostream>
#include <vector>
#include <string>
#include "timer.h"

#include "bintree.h"
#include "dictionary.h"
const char dpath[] =	"./diction.txt";

int main() {
	using namespace std;
	
	vector<string> vs;
	getDictionary( back_inserter(vs), 5000, SORTED, dpath );
	BinaryTree<string> tree;
	for( vector<string>::iterator i(vs.begin()); i != vs.end(); ++i )
		tree.insert( *i );
	{
	Timer t;
	for( vector<string>::iterator i(vs.begin()); i != vs.end(); ++i )
		const string *tmp( tree.find(*i) );
	cout << "find (normal return): " << t << endl;
	}
	{
	Timer t;
	for( vector<string>::iterator i(vs.begin()); i != vs.end(); ++i )
		const string *tmp( tree.efind(*i) );
	cout << "efind (exception return): " << t << endl;
	}
		
	return 0;
}
