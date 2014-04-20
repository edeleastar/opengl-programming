#include "util.h"

template <typename T>
void print(deque<T> v)
{
  foreach( T&i, v )
  {
    cout << i << ",";
  }
}

void dequetest()
{
  deque<int> dq;
  dq.push_back(3);
  dq.push_front(1);
  dq.insert(dq.begin()+1, 2);
  dq[2] = 0;
  print(dq.begin(), dq.end());
}
