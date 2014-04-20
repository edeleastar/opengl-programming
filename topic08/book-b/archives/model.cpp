#include "model.h"

using namespace std;
using namespace boost;

Model::Model()
{
}

bool Model::load(istream& is)
{
  string indicator;
  is >> indicator;
  while (!is.eof())
  {
    if (indicator == "#")
    {
      string buf;
      getline(is, buf);
    }
    else if (indicator == "g")
    {
      string name;
      is >> name;
      if (name == "default")
      {
        defaultGroup.load(is);
      }
      else
      {
        Geometry a(name, is, &defaultGroup);
        if (entities.find(a.name) == entities.end())
        {
          entities[a.name] = a;
        }
      }
    }
    is >> indicator;
  }
  return true;
}

void Model::render()
{
  foreach (GeometryMap::value_type &value, entities)
  {
    value.second.render();
  }
}

