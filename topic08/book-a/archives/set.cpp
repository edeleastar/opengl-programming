#include "util.h"


template <typename T, class Comp>
void print(std::set<T, Comp> s)
{
  foreach( T i, s )
  {
    cout << i << ",";
  }
}

struct ltstr
{
  bool operator() (const char* s1, const char* s2) const
  {
    return (strcmp(s1, s2) < 0);
  }
};

void settest()
{
  const char* str[6] = {"isomer", "ephemeral", "prosaic",
                        "nugatory", "artichoke", "serif"};

 // set<const char*, ltstr> s;
//  for (int i=0; i<6; i++)///
//  {
//	  s.insert(str[i]);
 // }

  set<const char*, ltstr> s(str, str + 6);

  print(s.begin(), s.end());
  print (s);
}
