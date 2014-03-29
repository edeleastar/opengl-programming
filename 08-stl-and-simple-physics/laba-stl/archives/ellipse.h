#pragma once

#include "shape.h"

struct Ellipse : public Shape
{
  int radius;

  Ellipse()
  { cout << "creating ellipse with default constructor" << endl;}

  Ellipse(Point o, int r) : Shape(o), radius(r)
  { cout << "creating ellipse with parameterised constructor" << endl;}

  virtual ~Ellipse()
  { cout << "Ellipse being destroyed.." << endl;}

  virtual void draw()
  {
    cout << "Ellipse with Origin: ";
    origin.print();
    cout << " and Radius: " << radius << endl;
  }

  Shape* clone() const
  {
   return new Ellipse(origin, radius);
  }
};
