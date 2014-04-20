#pragma once

#include "libs.h"
#include "vector3.h"

struct VertexGroup
{
  std::vector <Vector3> vertices;

  VertexGroup();
  void load(std::istream&);
};
