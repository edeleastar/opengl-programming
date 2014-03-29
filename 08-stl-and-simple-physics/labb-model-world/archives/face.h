#pragma once
#include "libs.h"
#include "vector3.h"

struct Face
{
  std::vector<int> vertexIndices;
  std::vector<int> textureIndices;

  Face(std::istream& is);
  void render(std::vector <Vector3>&);
};
