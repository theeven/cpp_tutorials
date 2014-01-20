#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <list>
#include "../ESTLUtil.h"

using namespace ESTLUtils;
using namespace std;

const int iterations = 150000;

int main() {
    cout << "Hello, Advanced C++ World!" << endl;
    return 0;
}

class UtilsDemo {
public:
    int go();
};

int UtilsDemo::go() {
    using namespace std;
    vector<int> v; // The "old" way to stuff a container with values:
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    show(v); // The easiest way to display the contents

    Timer t;

    for (int i = 0; i < iterations; ++i) {
        vector<int> w; // The "ESTLUtil.h" way:
        generate_n(back_inserter(w), 10, makeSequence(50));
        if (i == iterations - 1)
            show(w);
    }
    cout << iterations << " iterations of the loop took " << t << " seconds.";

    return 0;
}

class errSample {
public:
    int go();
};

int errSample::go() {
    using namespace std;

    typedef multimap<string, int> msi;
    msi mm;

    // These are OK:
    mm.insert(make_pair(string("Dave Gray"), 60));
    mm.insert(make_pair(string("Lisa Gray"), 60));
    mm.insert(make_pair(string("Jan Gray"), 42));

    // This is not:
    //	mm.insert(string("Leor"), 42);

    return 0;
}

class tdebug {
public:
    int go();
};

int tdebug::go() {
    int nums[] = {1, 12, 41, 59, 72};
    int nums2[] = {7, 19, 47, 51, 99};
    const size_t size = sizeof (nums) / sizeof (int);

    list<int> li(nums, nums + size);
    vector<int> vi(nums2, nums2 + size);

    list<int> result;
    merge(li.begin(), li.end(), vi.begin(), vi.end(), back_inserter(result));
    cout << "After good merge: " << endl;
    show(result);

    /*
            // Give list iterators in wrong order:
            result.clear();
            merge(li.end(), li.begin(), vi.begin(), vi.end(), back_inserter(result));
            cout << "After bad merge #1: " << endl;
            show(result);
     */

    /*
            // Give vector iterators in wrong order:
            result.clear();
            merge(li.begin(), li.end(), vi.end(), vi.begin(), back_inserter(result));
            cout << "After bad merge #2: " << endl;
            show(result);
     */

    /*
            // forget to use back_inserter for result:
            result.clear();
            merge(li.begin(), li.end(), vi.begin(), vi.end(), result.begin());
            cout << "After bad merge #3: " << endl;
            show(result);
     */

    return 0;
}
