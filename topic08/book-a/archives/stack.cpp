#include "util.h"

void stacktest()
{
  stack<int> s;
  s.push(8);
  s.push(5);
  s.push(6);
  cout << s.top() << endl;
  s.pop();
  cout << s.top() << endl;
}
