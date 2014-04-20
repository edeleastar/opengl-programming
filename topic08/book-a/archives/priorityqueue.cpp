#include "util.h"

void priorityqueuetest()
{
  priority_queue <int, vector<int>, greater<int> > pq;

  pq.push(2);
  pq.push(5);
  pq.push(3);
  pq.push(1);
  cout<<"pq contains " << pq.size() << " elements.\n";

  while (!pq.empty())
  {
    cout << pq.top() << endl;
    pq.pop();
  }
}
