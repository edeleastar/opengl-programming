#pragma once

#include "physicsactor.h"

struct SphereActor : public PhysicsActor
{
    float radius;
    
    SphereActor(Geometry *);
};
