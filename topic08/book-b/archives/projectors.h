#pragma once
#include "libs.h"
#include "projection.h"

struct Projectors
{
  Projectors();

  bool isPerspective();
  void keyPress(unsigned char key);
  void windowReshape(int w, int h);

  void addProjection(std::string, Projection *projection);

  ProjectionMap projections;
  Projection   *currentProjection;
};
