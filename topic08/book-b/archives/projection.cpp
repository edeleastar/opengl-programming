#include "projection.h"
#include "vector3.h"

void Projection::resize(Range size)
{
  windowSize = size;
}

Orthographic::Orthographic(Range x, Range y, Range z, int theAngle, Vector3 theAxis)
: xRange(x), yRange(y), zRange(z), angle(theAngle), axis(theAxis)
{
}

void Orthographic::render()
{
  glLoadIdentity();
  glViewport(0, 0, windowSize.first, windowSize.second);
  glMatrixMode ( GL_PROJECTION);
  glLoadIdentity();
  glOrtho(xRange.first, xRange.second, yRange.first, yRange.second, zRange.first, zRange.second);
  glMatrixMode ( GL_MODELVIEW);

  axis.rotate(angle);
}

Perspective::Perspective (float fovy, Range zRange, float zDistance)
: fovy(fovy), zRange(zRange), zDistance(zDistance)
{
}

void Perspective::render()
{
  glLoadIdentity();
  glViewport(0, 0, windowSize.first, windowSize.second);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fovy, windowSize.first/windowSize.second, zRange.first, zRange.second);
  glMatrixMode (GL_MODELVIEW);
  Vector3(0,0,zDistance).translate();
}
