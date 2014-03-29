#pragma once
#include "libs.h"
#include "renderable.h"
#include "geometry.h"

struct Actor : public Renderable
{
  Geometry *geometry;

  Actor(Geometry* g) : geometry(g)
  {}

  void render()
  { geometry->render(); }
};

typedef boost::ptr_map<std::string, Actor> ActorMap;

