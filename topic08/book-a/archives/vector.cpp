#include "util.h"

template <typename T>
void print4(vector<T> v)
{
  copy (v.begin(), v.end(), ostream_iterator<T> (cout, "\n"));
}

template <typename T>
void print3(vector<T> v)
{
  foreach( T&i, v )
  {
    cout << i << ",";
  }
}

template <typename T>
void print2(vector<T> v)
{
  typename std::vector<T>::iterator iter;

  for (iter = v.begin(); iter != v.end(); iter++)
  {
    cout << *iter << ",";
  }
}

void print1(vector<int> v)
{
  for (vector<int>::iterator i = v.begin(); i != v.end(); i++)
  {
    cout << *i << ",";
  }
}

void print0(vector<int> v)
{
  for (unsigned int i = 0; i < v.size(); i++)
  {
    cout << v[i] << ",";
  }
}
void vectest()
{
  vector<int> v;
  v.push_back(10);
  v.push_back(20);
  print (v.begin(), v.end());
  cout << v.size() << ' ' << v.capacity() << endl;
  v.pop_back();
  print3(v);
  cout << v.size() << ' ' << v.capacity() << endl;
}
