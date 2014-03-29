#pragma once
#include <iostream>
using namespace std;

struct Point
{
  int x,y;

  Point()
  {}

  Point(int x, int y) : x(x), y(y)
  {}

  void print()
  {
    cout << "X: " << x << " Y: " << y;
  }
};
