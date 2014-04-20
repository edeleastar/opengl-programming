#pragma once
#include "camera.h"

struct Cameras
{
  Cameras();

  void keyPress(unsigned char key);
  void addCamera(std::string str, Camera *camera);

  CameraMap  theCameras;
  Camera    *currentCamera;
};
