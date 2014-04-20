#pragma once
#include "vector3.h"

struct Camera
{
  Camera();
  void keyStroke (unsigned char key);
  void update(float secs);
  void render();


  float xrot;
  float yrot;
  Vector3 position;
  float controlPrecision;
  float zoomPrecision;
};
