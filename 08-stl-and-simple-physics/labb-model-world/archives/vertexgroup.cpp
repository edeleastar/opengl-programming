#include "vertexgroup.h"

using namespace std;

VertexGroup::VertexGroup()
{}

void VertexGroup::load(istream& is)
{
  string indicator;
  bool stillGroup=true;
  do
  {
    is >> indicator;
    if (indicator == "v")
    {
      vertices.push_back(Vector3(is));
    }
    else if (indicator == "g")
    {
      stillGroup = false;
    }
    else
    {
      string buf;
      getline(is, buf);
    }
  } while (stillGroup && !is.eof());
  is.putback(indicator[0]);
}
