#include "util.h"

typedef map<string, int> MyMap;

void print(MyMap& m)
{
  foreach (MyMap::value_type &i, m)
  {
    cout << i.second << endl;
  }
}

template <typename Iterator>
void printmap (Iterator start, Iterator  end)
{
  while (start != end)
  {
    cout << start->second << endl;
    start++;
  }
}

void maptest()
{
  MyMap grade;
  grade["Mark"] = 95;
  grade["Edward"] = 87;
  grade["Louise"] = 66;
  grade["Allen"] = 76;
  printmap(grade.begin(), grade.end());
  print(grade);
  cout << grade["Allen"] << endl;

  MyMap::iterator e;
}


