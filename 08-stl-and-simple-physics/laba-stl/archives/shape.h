#pragma once
#include "point.h"
#include <boost/utility.hpp>

struct Shape : private boost::noncopyable
{
  Point origin;

  Shape()
  { cout << "creating shape with default constructor" << endl;}

  Shape(Point p) : origin(p)
  { cout << "creating shape with parameterised construtor" << endl;}

  virtual ~Shape()
  { cout << "Shape being destroyed.." << endl;}

  virtual void draw()=0;

  virtual Shape* clone() const
  {return 0;};
};
