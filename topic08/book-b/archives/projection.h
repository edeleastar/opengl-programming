#pragma once
#include "libs.h"
#include "vector3.h"

typedef std::pair<float, float> Range;

struct Projection
{
  Range windowSize;

  void resize(Range size);
  virtual void render()=0;
};

struct Orthographic: public Projection
{
  Range xRange;
  Range yRange;
  Range zRange;
  Vector3 axis;
  int angle;

  Orthographic(Range x, Range y, Range z, int angle, Vector3 axis);
  void render();
};

struct Perspective : public Projection
{
  float fovy;
  Range zRange;
  float zDistance;

  Perspective (float fovy, Range zRange, float zDistance);
  void render();
};

typedef boost::ptr_map <std::string, Projection>  ProjectionMap;

