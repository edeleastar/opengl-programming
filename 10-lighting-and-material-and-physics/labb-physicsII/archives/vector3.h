#pragma once
#include "libs.h"
#define _USE_MATH_DEFINES
#include <cmath>

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

    inline bool isUnit() const {
        return abs(lengthSqr()-1.0f)<=1.0e-5f;
    }
    
    inline const float&  operator[] (int i) const {return (&X)[i]; };
    inline float& operator[] (int i) {return (&X)[i]; };
    
    inline Vector3 operator- () const {
        return Vector3(-X, -Y, -Z);
    }
    
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
    
    inline Vector3& operator/= (float rhs)
    {
        return (*this *= (1.0f/rhs));
    }
    
    inline Vector3 operator- (const Vector3 rhs) const
    {
        return Vector3(X-rhs.X, Y-rhs.Y, Z-rhs.Z);
    }
    
    inline Vector3 operator+ (const Vector3 rhs) const
    {
        return Vector3(X+rhs.X, Y+rhs.Y, Z+rhs.Z);
    }
    
    inline Vector3 operator* (float rhs) const
    {
        return Vector3(X*rhs, Y*rhs, Z*rhs);
    }
    
    inline Vector3 operator/ (float rhs) const
    {
        return (*this) * (1.0f/rhs);
    }

    inline Vector3 direction () const {
        const float lenSquared = lengthSqr();
        const float invSqrt = 1.0f / sqrtf(lenSquared);
        return Vector3(X * invSqrt, Y * invSqrt, Z * invSqrt);
    }
    
    inline float lengthSqr () const {   return (X*X + Y*Y + Z*Z);   }
    inline float length () const {   return sqrt(lengthSqr());   }
    
    inline Vector3 cross (const Vector3& rhs) const {
        return Vector3(Y*rhs.Z - Z*rhs.Y, Z*rhs.X - X*rhs.Z,
                       X*rhs.Y - Y*rhs.X);
    }
    
    inline float dot (const Vector3& rhs) const {
        return (X*rhs.X + Y*rhs.Y + Z*rhs.Z);
    }
    
    
    friend std::ostream& operator <<(std::ostream& outputStream, const Vector3& v);
};


inline Vector3 operator* (float lhs, const Vector3& rhs)
{
    return rhs * lhs;
}

Vector3 findNormal(const Vector3& point1, const Vector3& point2, const Vector3& point3);
Vector3 cross (const Vector3& lhs, const Vector3& rhs);
float dot (const Vector3& lhs, const Vector3& rhs);

