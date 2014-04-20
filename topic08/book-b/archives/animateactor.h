#pragma once
#include "actor.h"

struct AnimateActor : public Actor
{
  AnimateActor(Geometry* geometry) : Actor (geometry)
  {}

  virtual void integrate(float dt)=0;
};

typedef std::map<std::string, AnimateActor*> AnimateActorMap;
