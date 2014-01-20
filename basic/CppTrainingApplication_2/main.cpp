/* 
 * File:   main.cpp
 * Author: panchal
 *
 * CopySort: STL Generic Algorithms: p17
 * 
 * Created on January 25, 2012, 10:11 AM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    vector<string> names;
    copy(istream_iterator<string> (cin), istream_iterator<string> (), back_inserter(names));
    sort(names.begin(), names.end());
    unique_copy(names.begin(), names.end(), ostream_iterator<string> (cout, "\n"));
    return 0;
}

