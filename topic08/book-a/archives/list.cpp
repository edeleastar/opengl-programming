#include "util.h"

template <typename T>
void print(list<T> v)
{
  foreach( T&i, v )
  {
    cout << i << ",";
  }
}

void listtest()
{
  list<int> la, lb;

  la.push_back(2), la.push_back(1), la.push_back(5);

  lb.push_back(4), lb.push_back(3);

  la.sort();
  lb.sort();
  la.merge(lb);
  print(la.begin(), la.end());
  print(la);
}
