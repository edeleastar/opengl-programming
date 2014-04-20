#pragma once

#include "vector3.h"
#include "quat.h"

class Matrix3 {
private:
  float elt[3][3];

public:

  // constructors
  Matrix3 () {};      // uninitialised for performance
   
  Matrix3 (float fEntry00, float fEntry01, float fEntry02,
       float fEntry10, float fEntry11, float fEntry12,
       float fEntry20, float fEntry21, float fEntry22);

  // special matrices
  static const Matrix3& zero();
  static const Matrix3& identity();

  void set(float fEntry00, float fEntry01, float fEntry02,
       float fEntry10, float fEntry11, float fEntry12,
       float fEntry20, float fEntry21, float fEntry22);


  Matrix3(const class Quat& q);

  // uniary operators
  inline float* operator[] (int iRow) {
    return (float*)&elt[iRow][0];
  }

  inline const float* operator[] (int iRow) const {
    return (const float*)&elt[iRow][0];
  }

  Matrix3 transpose () const;
  bool inverse (Matrix3& rkInverse, float fTolerance = 1e-06) const;
  Matrix3 inverse (float fTolerance = 1e-06) const;

  // binary operators
  Matrix3 operator* (const Matrix3& rkMatrix) const;

  inline Vector3 operator* (const Vector3& v) const {
    Vector3 kProd;
    
    for (int r = 0; r < 3; ++r) {
      kProd[r] =
      elt[r][0] * v[0] +
      elt[r][1] * v[1] +
      elt[r][2] * v[2];
    }
    
    return kProd;
  }

    void toAxisAngle(Vector3& rkAxis, float& rfRadians) const;

    static Matrix3 fromAxisAngle(const Vector3& rkAxis, float fRadians);
    
	/** Assumes that rkAxis has unit length */
    static Matrix3 fromUnitAxisAngle(const Vector3& rkAxis, float fRadians);
    
    /**
     * The matrix must be orthonormal.  The decomposition is yaw*pitch*roll
     * where yaw is rotation about the Up vector, pitch is rotation about the
     * right axis, and roll is rotation about the Direction axis.
     */
    bool toEulerAnglesXYZ (float& rfYAngle, float& rfPAngle,
                           float& rfRAngle) const;
    bool toEulerAnglesXZY (float& rfYAngle, float& rfPAngle,
                           float& rfRAngle) const;
    bool toEulerAnglesYXZ (float& rfYAngle, float& rfPAngle,
                           float& rfRAngle) const;
    bool toEulerAnglesYZX (float& rfYAngle, float& rfPAngle,
                           float& rfRAngle) const;
    bool toEulerAnglesZXY (float& rfYAngle, float& rfPAngle,
                           float& rfRAngle) const;
    bool toEulerAnglesZYX (float& rfYAngle, float& rfPAngle,
                           float& rfRAngle) const;
    static Matrix3 fromEulerAnglesXYZ (float fYAngle, float fPAngle, float fRAngle);
    static Matrix3 fromEulerAnglesXZY (float fYAngle, float fPAngle, float fRAngle);
    static Matrix3 fromEulerAnglesYXZ (float fYAngle, float fPAngle, float fRAngle);
    static Matrix3 fromEulerAnglesYZX (float fYAngle, float fPAngle, float fRAngle);
    static Matrix3 fromEulerAnglesZXY (float fYAngle, float fPAngle, float fRAngle);
    static Matrix3 fromEulerAnglesZYX (float fYAngle, float fPAngle, float fRAngle);

};
