#pragma once

#include "shape.h"

struct Rectangle : public Shape
{
  int width, height;

  Rectangle()
  { cout << "creating rectangle with default constuctor" << endl;}

  Rectangle (Point topleft, int w, int h): Shape(topleft), width(w), height(h)
  { cout << "creating rectangle with parameterised constructor" << endl;}

  virtual ~Rectangle()
  { cout << "Rectangle being destroyed.." << endl;}


  virtual void draw()
  {
    cout << "Rectangle with Origin: ";
    origin.print();
    cout << " and Width: " << width << " Height: " << height << endl;
  }

  Shape* clone() const
  {
    return new Rectangle(origin, width, height);
  }
};
