#pragma once

#include "vector3.h"
#include "matrix3.h"

class Matrix3;

class Quat {
public:

    // quaterion elements:
    //      q = [sin(angle / 2) * axis, cos(angle / 2)]
    //      In Watt & Watt's notation, s = w, v = (x, y, z)
    //      In the Real-Time Rendering notation, u = (x, y, z), w = w 
    float x, y, z, w;

    //Initializes to a zero degree rotation, (0,0,0,1)
    Quat() : x(0), y(0), z(0), w(1) {}

    Quat(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
 
    Quat(const Matrix3& rot);

    Quat(const Quat & other) : x(other.x), y(other.y), z(other.z), w(other.w) {}
    
    Quat(const Vector3& v, float w = 0) : x(v.X), y(v.Y), z(v.Z), w(w) {}
    
    float dot(const Quat& other) const {
        return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);
    }
    
    /// Make unit length in place
    void unitize() {
        *this *= (1.0f/sqrt(dot(*this)));
    }

    Quat toUnit() const {
        Quat x = *this;
        x.unitize();
        return x;
    }

    const float& real() const { return w; }
    float& real() { return w; }
    

    const Vector3& imag() const {
        return *(reinterpret_cast<const Vector3*>(this));
    }
    
    Vector3& imag() {
        return *(reinterpret_cast<Vector3*>(this));
    }

    
    Quat operator-() const {
        return Quat(-x, -y, -z, -w);
    }
    
    Quat operator-(const Quat& other) const {
        return Quat(x - other.x, y - other.y, z - other.z, w - other.w);
    }
    
    Quat& operator-=(const Quat& q) {
        x -= q.x; y -= q.y; z -= q.z; w -= q.w;
        return *this;
    }
    
    Quat operator+(const Quat& q) const {
        return Quat(x + q.x, y + q.y, z + q.z, w + q.w);
    }
    
    Quat& operator+=(const Quat& q) {
        x += q.x; y += q.y; z += q.z; w += q.w;
        return *this;
    }
    
    Quat operator*(float s) const {
        return Quat(x * s, y * s, z * s, w * s);
    }

    friend Quat operator* (float s, const Quat& q);

    Quat operator*(const Quat& other) const;

    Quat& operator*=(float s) {
        x *= s; y *= s; z *= s; w *= s;
        return *this;
    }

    void toAxisAngleRotation(Vector3& axis, float& angle) const;
    Matrix3 toRotationMatrix() const;
    void toRotationMatrix(Matrix3& rot) const;
    
    friend std::ostream& operator <<(std::ostream& outputStream, const Quat& q);

};

inline Quat operator*(float s, const Quat& q) {
    return q * s;
}

