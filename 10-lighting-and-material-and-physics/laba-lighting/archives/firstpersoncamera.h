#pragma once

#include "camera.h"

struct FirstPersonCamera : public Camera
{
  FirstPersonCamera()
  {}

  virtual void keyStroke (unsigned char key);
  void render();
};
