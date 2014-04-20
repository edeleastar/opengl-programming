#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <stack>
#include <queue>

using namespace std;

template <typename Iterator>
void print (Iterator start, Iterator  end)
{
  while (start != end)
  {
    cout << *start << ", ";
    start++;
  }
}



