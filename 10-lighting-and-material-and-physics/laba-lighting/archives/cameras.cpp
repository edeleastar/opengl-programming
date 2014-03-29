#include "cameras.h"
#include "thirdpersoncamera.h"
#include "firstpersoncamera.h"

using namespace std;

Cameras::Cameras()
{
  currentCamera = new ThirdPersonCamera();
  addCamera("5", currentCamera);
  addCamera("6", new FirstPersonCamera());
}

void Cameras::addCamera(std::string str, Camera *camera)
{
  theCameras.insert(str, camera);
}

void Cameras::keyPress(unsigned char key)
{
  string cameraname;
  cameraname+=key;
  CameraMap::iterator iter = theCameras.find(cameraname);
  if (iter != theCameras.end())
  {
    currentCamera = iter->second;
  }
}
