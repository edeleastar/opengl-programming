#pragma once
#include "libs.h"
#include <cmath>
#include "vector3.h"

struct Vector4
{
  float x, y, z, w;

  inline const float&  operator[] (int i) const {return (&x)[i]; };
  inline float& operator[] (int i) {return (&x)[i]; };

  static const Vector4& zero();

  Vector4() : x(0), y(0), z(0), w(0) {};
  Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};
  Vector4(const Vector3 v, float w) : x(v.X), y(v.Y), z(v.Z), w(w) {};


  // binary operators
  float dot (const Vector4& rhs) const
  {
    return x*rhs.x + y*rhs.y + z*rhs.z + w*rhs.w;
  }

  Vector3 xyz() const  { return Vector3(x, y, z); }
};

float dot (const Vector4& lhs, const Vector4& rhs);
