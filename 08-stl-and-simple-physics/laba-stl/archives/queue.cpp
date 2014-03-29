#include "util.h"

void queuetest()
{
  queue<int> q;
  q.push(8);
  q.push(5);
  q.push(6);
  cout << q.front() << endl;
  q.pop();
  cout << q.front() << endl;
}
