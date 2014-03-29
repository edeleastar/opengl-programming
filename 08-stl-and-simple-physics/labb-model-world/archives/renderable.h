#pragma once
#include "libs.h"

struct Renderable
{
  virtual void render()=0;
};

typedef boost::ptr_map<std::string, Renderable> RenderableMap;


