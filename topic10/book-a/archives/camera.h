#pragma once
#include "vector3.h"

struct Camera
{
  Camera()
  : position(0,0,0), xrot(0), yrot(0)
  {}

  virtual void specialKeyboard (int key, int x, int y)
  {}

  virtual void keyStroke (unsigned char key)
  {}

  virtual void mouseMovement(int x, int y)
  {}

  virtual void render()=0;

  Vector3 position;
  float xrot, yrot, cRadius;
};

typedef boost::ptr_map <std::string, Camera>  CameraMap;


