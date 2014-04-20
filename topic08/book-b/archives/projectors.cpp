#include "projectors.h"
using namespace std;
using namespace boost;

Projectors::Projectors()
{
  currentProjection = new Perspective(60, Range(1,1000), -5);

  addProjection("1", currentProjection);
  addProjection("2", new Orthographic (Range(-10,10), Range(-10,10), Range(-10,10), 90, Vector3::UnitX));
  addProjection("3", new Orthographic (Range(-10,10), Range(-10,10), Range(-10,10), 90, Vector3::UnitY));
  addProjection("4", new Orthographic (Range(-10,10), Range(-10,10), Range(-10,10), 90, Vector3::UnitZ));
}

bool Projectors::isPerspective()
{
  Perspective *p = dynamic_cast<Perspective*> (currentProjection);
  if (p)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void Projectors::keyPress(unsigned char ch)
{
  Range windowSize = currentProjection->windowSize;
  string projection;
  projection+=ch;
  ProjectionMap::iterator iter = projections.find(projection);
  if (iter != projections.end())
  {
    currentProjection = iter->second;
    currentProjection->resize(windowSize);
    currentProjection->render();
  }
}

void Projectors::addProjection(std::string str, Projection *projection)
{
  projections.insert(str, projection);
}

void Projectors::windowReshape(int w, int h)
{
  currentProjection->resize(Range(w,h));
  currentProjection->render();
}



