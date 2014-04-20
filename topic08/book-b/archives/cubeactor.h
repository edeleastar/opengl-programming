#pragma once
#include "libs.h"
#include "vector3.h"
#include "animateactor.h"

struct CubeActor : public AnimateActor
{
  Vector3 position;
  Vector3 velocity;
  Vector3 acceleration;

  Vector3 force;

  float inverseMass;
  float damping;

  CubeActor(Geometry *);

  void integrate(float dt);
  void render();
};

