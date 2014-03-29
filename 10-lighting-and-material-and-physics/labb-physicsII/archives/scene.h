#pragma once
#include "libs.h"
#include "model.h"
#include "actor.h"
#include "animateactor.h"
#include "forcegeneratorregistry.h"

struct Scene
{
  Scene(Model*);

  void render();
  void tick(float secondsDelta);

  ActorMap         actors;
  AnimateActorMap  animateActors;
    
  ForceGeneratorRegistry forceGeneratorRegistry;
};
