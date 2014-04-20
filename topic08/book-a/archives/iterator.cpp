#include "util.h"

void iteratortest()
{
  vector<int> v;
  int ary[6] = {1, 4, 2, 8, 5, 7};
  for (int i = 0; i < 6; v.push_back(ary[i++]));

  for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
  {
	cout << (*it) << " ";
  }
  cout << endl;
  copy (v.begin(), v.end(), ostream_iterator<int>(cout, " "));
}
