//
// This is a full-blown demonstration program using Scott Meyers' ESTLUtil.h
// package.
//
// For a much simpler example, see "UtilsDemo.cpp" in the "00_Demo" folder.
//
// NOTE: The filename of the header file is "ESTLUtil.h", but the namespace name
//       is "ESTLUtils" (trailing 's')
//

#include <vector>
#include <deque>
#include <list>
#include <map>
#include "ESTLUtil.h"

int main()
{
  using namespace ESTLUtils;
  using namespace std;

  Timer t;

  const char words[] = "This is a test";

  // print contents of a string
  string test(words);
  printContainer("test", test);
  printContainer(test);
#if (!defined(__GNUC__) || __GNUC__ == 3)
  // g++ 2 resolves this call incorrectly, so we skip this test for pre-v3 g++
  printContainer(test, clog);
#endif
  printContainer("test", test, cerr);
  cout << endl;

  // print a container of char*
  list<char*> l1;
  l1.push_back("Hello");
  l1.push_back("Goodbye");
  l1.push_back("Greetings!");
  printContainer("l1", l1);
  printContainer(l1);
  printContainer(l1, cerr);
  printContainer("l1", l1, clog);
  cout << endl;

  // print a container of const char*
  list<const char*> l2;
  l2.push_back("Hello");
  l2.push_back("Goodbye");
  l2.push_back("Greetings!");
  printContainer("l2", l2);
  printContainer(l2);
  printContainer(l2, cerr);
  printContainer("l2", l2, clog);
  cout << endl;

  vector<int> v1;
  generate_n(back_inserter(v1), 5, makeSequence());
  generate_n(back_inserter(v1), 3, makeSequence(-5));
  generate_n(back_inserter(v1), 5, makeSequence(10, 5));
  
  // print contents of a vector
  printContainer("v1", v1);
  printContainer(v1);
  printContainer(v1, clog);
  printContainer("v1", v1, cerr);
  cout << endl;

  deque<double> d;
  generate_n(back_inserter(d), 10, makeSequence(0.5, 1.0));

  // print contents of a deque
  printContainer("d", d);
  printContainer(d);
  printContainer(d, cerr);
  printContainer("d", d, clog);
  cout << endl;

  vector<int*> v2;
  for (int i = 0; i < 5; ++i) v2.push_back(new int(10-i));

  // print contents of a vector of pointers
  printContainer("v2", v2);
  printContainer(v2);
  printContainer(v2, clog);
  printContainer("v2", v2, cerr);
  cout << endl;

  // print contents of a map
  map<int, const char*> m;
  m[95] = "Scott";
  m[36] = "Nancy";
  m[59] = "Persephone";
  m[3] = "Phyllis";
  printContainer("m", m);
  cout << endl;

  // print two containers
  printContainers(v1, v2);
  printContainers(v1, v2, clog);
  printContainers("v1", v1, "v2", v2);
  printContainers("v1", v1, "v2", v2, clog);
  cout << endl;

  cout << "testing show() and show() macros on vectors:" << endl;
  show(v1);
  show2(v1, v2);

  cout << "testing show() and show() macros on maps:" << endl;
  show(m);
  show2(m, m);


  cout << "Time: " << t << " seconds.\n";
  t.reset();

  return 0;
}
