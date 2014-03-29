#pragma once
#include <istream>
#include <sstream>

struct Vector3
{
  float X;
  float Y;
  float Z;

  static Vector3 UnitX;
  static Vector3 UnitY;
  static Vector3 UnitZ;

  Vector3(float x, float y, float z);
  Vector3(float value);
  Vector3();
  Vector3(std::istream& is);

  void translate();
  void rotate (float angle);

  void render();

  static const Vector3 & zero();

  inline Vector3& operator= (const Vector3& rhs)
  {
    X = rhs.X;   Y = rhs.Y;   Z = rhs.Z;
    return *this;
  }

  inline Vector3& operator+= (const Vector3& rhs)
  {
    X += rhs.X;   Y += rhs.Y;   Z += rhs.Z;
    return *this;
  }

  inline Vector3& operator-= (const Vector3& rhs)
  {
    X -= rhs.X;   Y -= rhs.Y;   Z -= rhs.Z;
    return *this;
  }

  inline Vector3& operator*= (float rhs)
  {
    X *= rhs;   Y *= rhs;   Z *= rhs;
    return *this;
  }

  inline Vector3 operator+ (const Vector3 rhs) const
  {
    return Vector3(X+rhs.X,Y+rhs.Y, Z+rhs.Z);
  }

  inline Vector3 operator* (float rhs) const
  {
    return Vector3(X*rhs,Y*rhs, Z*rhs);
  }
 
  friend std::ostream& operator <<(std::ostream& outputStream, const Vector3& v);
};


inline Vector3 operator* (float lhs, const Vector3& rhs)
{
  return rhs * lhs;
}
