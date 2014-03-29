#pragma once
#include "libs.h"
#include "geometry.h"
#include "vertexgroup.h"

struct Model : public Renderable
{
  GeometryMap entities;
  VertexGroup defaultGroup;

  Model();
  bool load(std::istream &is);
  void render();
};
