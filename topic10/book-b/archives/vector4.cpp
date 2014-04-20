#include "vector4.h"

const Vector4& Vector4::zero()
{
  static const Vector4 v(0,0,0,0);
  return v;
}

float dot (const Vector4& lhs, const Vector4& rhs)
{
  return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z + lhs.w*rhs.w;
}
