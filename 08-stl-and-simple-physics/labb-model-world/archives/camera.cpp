#include "libs.h"
#include "camera.h"
#include <math.h>
#include <stdlib.h>

#define GL_PI 3.1415

using namespace std;

Camera::Camera()
: position (0,0,-10)
{
  controlPrecision = 0.5;
  zoomPrecision = 0.1;
}

void Camera::render()
{
  Vector3::UnitX.rotate(xrot);
  Vector3::UnitY.rotate(yrot);
  position.translate();
}

void Camera::update(float dt)
{
}

void Camera::keyStroke (unsigned char key)
{
  if (key == 'q')
  {
    xrot += controlPrecision;
    if (xrot > 360)
      xrot -= 360;
  }
  else if (key == 'z')
  {
    xrot -= controlPrecision;
    if (xrot < -360)
      xrot += 360;
  }
  else if (key == 'd')
  {
    yrot += controlPrecision;
    if (yrot > 360)
      yrot -= 360;
  }
  else if (key == 'a')
  {
    yrot -= controlPrecision;
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
      position.Z -= float(cos(yrotrad))  * zoomPrecision;
      //position.Z -= controlPrecision;
      cout << position.Z << endl;
    }
    else if (key == 's')
    {
      position.X -= float(sin(yrotrad));
      position.Y += float(sin(xrotrad));
      position.Z += float(cos(yrotrad)) * zoomPrecision;
      //position.Z += controlPrecision;
      cout << position.Z << endl;
    }
  }
}
