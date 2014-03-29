#include "libopengl.h"
#include "vector3.h"

using namespace std;

Vector3 Vector3::UnitX(1.0f, 0.0f, 0.0f);
Vector3 Vector3::UnitY(0.0f, 1.0f, 0.0f);
Vector3 Vector3::UnitZ(0.0f, 0.0f, 1.0f);

Vector3::Vector3(float x, float y, float z)
: X(x)
, Y(y)
, Z(z)
{}

Vector3::Vector3(float value)
: X(value)
, Y(value)
, Z(value)
{}

Vector3::Vector3()
: X(0)
, Y(0)
, Z(0)
{}

Vector3::Vector3(istream &is)
{
  is >> X >> Y >> Z;
}

void Vector3::render()
{
  glVertex3f(X, Y, Z);
}

void Vector3::translate()
{
  glTranslatef(X,Y,Z);
}

void Vector3::rotate (float angle)
{
  glRotatef(angle, X,Y,Z);
}

// From here code added by KM

const Vector3& Vector3::zero()
{
  static const Vector3 v(0, 0, 0);
  return v;
}


Vector3 findNormal(const Vector3& point1, const Vector3& point2, const Vector3& point3)
{
  Vector3 v1, v2;

  // Calculate two vectors from the three points. Assumes counter clockwise winding
  v1.X = point1.X - point2.X;
  v1.Y = point1.Y - point2.Y;
  v1.Z = point1.Z - point2.Z;

  v2.X = point2.X - point3.Z;
  v2.Y = point2.Y - point3.Y;
  v2.Z = point2.Z - point3.Z;

  // Take the cross product of the two vectors to get he normal vector.
  Vector3 result;
  result.X =  v1.Y * v2.Z - v2.Y * v1.Z;
  result.Y = -v1.X * v2.Z + v2.X * v1.Z;
  result.Z =  v1.X * v2.Y - v2.X * v1.Y;
  return result;
}

Vector3 cross (const Vector3& lhs, const Vector3& rhs)  {
    return lhs.cross(rhs);
}

float dot (const Vector3& lhs, const Vector3& rhs) {
    return lhs.dot(rhs);
}


std::ostream& operator <<(std::ostream& outputStream, const Vector3& v)
{
	outputStream <<"(" <<v.X <<", " <<v.Y <<", " <<v.Z <<" )";
	return outputStream;
}