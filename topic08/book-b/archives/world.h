#pragma once
#include "libs.h"
#include "renderable.h"
#include "projectors.h"
#include "geometry.h"

#define theWorld World::GetInstance()

struct World
{
  void initialize(std::string name, int width, int height);
  void keyPress(unsigned char ch);
  void start();
  void render();

  static World& GetInstance();
  static World  *s_World;

  GeometryMap   *renderables;
  Projectors     projectors;
};

