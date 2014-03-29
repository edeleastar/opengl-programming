#include "libs.h"
#include "firstpersoncamera.h"
#include <math.h>
#include <stdlib.h>

#define GL_PI 3.1415

using namespace std;

void FirstPersonCamera::render()
{
  Vector3::UnitX.rotate(xrot);
  Vector3::UnitY.rotate(yrot);
  position.translate();
}

void FirstPersonCamera::keyStroke (unsigned char key)
{
  if (key == 'q')
  {
    xrot += .5;
    if (xrot > 360)
      xrot -= 360;
  }
  else if (key == 'z')
  {
    xrot -= .5;
    if (xrot < -360)
      xrot += 360;
  }
  else if (key == 'd')
  {
    yrot += .5;
    if (yrot > 360)
      yrot -= 360;
  }
  else if (key == 'a')
  {
    yrot -= .5;
    if (yrot < -360)
      yrot += 360;
  }

  else if (key == 'w' || key == 's')
  {
    float xrotrad, yrotrad;
    yrotrad = (yrot / 180 * GL_PI);
    xrotrad = (xrot / 180 * GL_PI);
    if (key == 'w')
    {
      position.X += float(sin(yrotrad));
      position.Y -= float(sin(xrotrad));
      position.Z -= float(cos(yrotrad));
    }
    else if (key == 's')
    {
      position.X -= float(sin(yrotrad));
      position.Y += float(sin(xrotrad));
      position.Z += float(cos(yrotrad));
    }
  }
}
