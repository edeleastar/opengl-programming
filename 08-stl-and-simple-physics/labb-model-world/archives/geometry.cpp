#include "geometry.h"
using namespace std;

Geometry::Geometry()
{
}

Geometry::Geometry(string groupName, istream& is, VertexGroup*group)
: name(groupName), vertexGroup(group)
{
  string indicator;
  bool stillGroup=true;
  do
  {
    is >> indicator;
    if (indicator == "f")
    {
      faces.push_back(Face(is));
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

void Geometry::render()
{
  foreach (Face &face, faces)
  {
    face.render(vertexGroup->vertices);
  }
}
