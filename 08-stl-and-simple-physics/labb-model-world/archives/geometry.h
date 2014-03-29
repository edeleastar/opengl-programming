#pragma once
#include "libs.h"
#include "vector3.h"
#include "face.h"
#include "vertexgroup.h"
#include "renderable.h"

struct Geometry : public Renderable
{
  std::string name;
  std::vector<Face> faces;
  VertexGroup *vertexGroup;

  Geometry();
  Geometry(std::string name, std::istream&, VertexGroup*);
  void render();
};

typedef std::map <std::string, Geometry>  GeometryMap;
