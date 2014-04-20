#pragma once

#include "vector3.h"
#include "vector4.h"
#include "matrix3.h"

class Matrix4 {
private:
    float elt[4][4];
    
public:
 
    // constructors 
    Matrix4 () {};          // uninitialised for performance
    
    Matrix4(float r1c1, float r1c2, float r1c3, float r1c4,
            float r2c1, float r2c2, float r2c3, float r2c4,
            float r3c1, float r3c2, float r3c3, float r3c4,
            float r4c1, float r4c2, float r4c3, float r4c4);

    // special matrices
    static const Matrix4& identity();
    static const Matrix4& zero();
    
    void set(float r1c1, float r1c2, float r1c3, float r1c4,
             float r2c1, float r2c2, float r2c3, float r2c4,
             float r3c1, float r3c2, float r3c3, float r3c4,
             float r4c1, float r4c2, float r4c3, float r4c4);

    Matrix4(const class Matrix3& upper3x3, const class Vector3& lastCol = Vector3::zero());

    // uninary operators
    Matrix4 transpose() const;

    Matrix4 adjoint() const;
    Matrix4 cofactor() const;
    float determinant() const;

    Matrix4 inverse() const;

    const Vector4& row(int r) const;
    Vector4 column(int c) const;

    // binary operators
    Matrix4 operator*(const float s) const; 
    Vector4 operator*(const Vector4& vector) const;
    
    class Vector3 homoMul(const class Vector3& v, float w) const;


private:
    float subDeterminant(int excludeRow, int excludeCol) const;
};