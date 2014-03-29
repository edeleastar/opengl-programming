#include "matrix3.h"

// constructors 
Matrix3::Matrix3(float fEntry00, float fEntry01, float fEntry02,
                 float fEntry10, float fEntry11, float fEntry12,
                 float fEntry20, float fEntry21, float fEntry22) {
    set(fEntry00, fEntry01, fEntry02,
        fEntry10, fEntry11, fEntry12,
        fEntry20, fEntry21, fEntry22);
}

// special matrices

const Matrix3& Matrix3::zero() {
    static Matrix3 m(0, 0, 0, 0, 0, 0, 0, 0, 0);
    return m;
}

const Matrix3& Matrix3::identity() {
    static Matrix3 m(1, 0, 0, 0, 1, 0, 0, 0, 1);
    return m;
}

void Matrix3::set(float fEntry00, float fEntry01, float fEntry02,
                  float fEntry10, float fEntry11, float fEntry12, 
                  float fEntry20, float fEntry21, float fEntry22) {
    
    elt[0][0] = fEntry00; elt[0][1] = fEntry01; elt[0][2] = fEntry02;
    elt[1][0] = fEntry10; elt[1][1] = fEntry11; elt[1][2] = fEntry12;
    elt[2][0] = fEntry20; elt[2][1] = fEntry21; elt[2][2] = fEntry22;
}


Matrix3::Matrix3(const Quat& _q) {

    Quat q = _q;
    q.unitize();
    float xx = 2.0f * q.x * q.x;
    float xy = 2.0f * q.x * q.y;
    float xz = 2.0f * q.x * q.z;
    float xw = 2.0f * q.x * q.w;
    
    float yy = 2.0f * q.y * q.y;
    float yz = 2.0f * q.y * q.z;
    float yw = 2.0f * q.y * q.w;
    
    float zz = 2.0f * q.z * q.z;
    float zw = 2.0f * q.z * q.w;
    
    set(1.0f - yy - zz,    xy - zw,        xz + yw,
        xy + zw,          1.0f - xx - zz,  yz - xw,
        xz - yw,          yz + xw,        1.0f - xx - yy);
}

// uniary operators

Matrix3 Matrix3::transpose () const {
    Matrix3 kTranspose;
    
    for (int iRow = 0; iRow < 3; iRow++) {
        for (int iCol = 0; iCol < 3; iCol++) {
            kTranspose[iRow][iCol] = elt[iCol][iRow];
        }
    }
    
    return kTranspose;
}

bool Matrix3::inverse (Matrix3& rkInverse, float fTolerance) const {
    // Invert a 3x3 using cofactors.  This is about 8 times faster than
    // the Numerical Recipes code which uses Gaussian elimination.
    
    rkInverse[0][0] = elt[1][1] * elt[2][2] -
    elt[1][2] * elt[2][1];
    rkInverse[0][1] = elt[0][2] * elt[2][1] -
    elt[0][1] * elt[2][2];
    rkInverse[0][2] = elt[0][1] * elt[1][2] -
    elt[0][2] * elt[1][1];
    rkInverse[1][0] = elt[1][2] * elt[2][0] -
    elt[1][0] * elt[2][2];
    rkInverse[1][1] = elt[0][0] * elt[2][2] -
    elt[0][2] * elt[2][0];
    rkInverse[1][2] = elt[0][2] * elt[1][0] -
    elt[0][0] * elt[1][2];
    rkInverse[2][0] = elt[1][0] * elt[2][1] -
    elt[1][1] * elt[2][0];
    rkInverse[2][1] = elt[0][1] * elt[2][0] -
    elt[0][0] * elt[2][1];
    rkInverse[2][2] = elt[0][0] * elt[1][1] -
    elt[0][1] * elt[1][0];
    
    float fDet =
    elt[0][0] * rkInverse[0][0] +
    elt[0][1] * rkInverse[1][0] +
    elt[0][2] * rkInverse[2][0];
    
    if ( abs(fDet) <= fTolerance )
        return false;
    
    float fInvDet = 1.0 / fDet;
    
    for (int iRow = 0; iRow < 3; iRow++) {
        for (int iCol = 0; iCol < 3; iCol++)
            rkInverse[iRow][iCol] *= fInvDet;
    }
    
    return true;
}

Matrix3 Matrix3::inverse (float fTolerance) const {
    Matrix3 kInverse = Matrix3::zero();
    inverse(kInverse, fTolerance);
    return kInverse;
}


// binary operators

Matrix3 Matrix3::operator* (const Matrix3& rkMatrix) const {
    Matrix3 kProd;
    
    for (int iRow = 0; iRow < 3; iRow++) {
        for (int iCol = 0; iCol < 3; iCol++) {
            kProd.elt[iRow][iCol] =
            elt[iRow][0] * rkMatrix.elt[0][iCol] +
            elt[iRow][1] * rkMatrix.elt[1][iCol] +
            elt[iRow][2] * rkMatrix.elt[2][iCol];
        }
    }
    
    return kProd;
}

//----------------------------------------------------------------------------
void Matrix3::toAxisAngle (Vector3& rkAxis, float& rfRadians) const {
    // 
    // Let (x,y,z) be the unit-length axis and let A be an angle of rotation.
    // The rotation matrix is R = I + sin(A)*P + (1-cos(A))*P^2 (Rodrigues' formula) where
    // I is the identity and
    //
    //       +-        -+
    //   P = |  0 -z +y |
    //       | +z  0 -x |
    //       | -y +x  0 |
    //       +-        -+
    //
    // If A > 0, R represents a counterclockwise rotation about the axis in
    // the sense of looking from the tip of the axis vector towards the
    // origin.  Some algebra will show that
    //
    //   cos(A) = (trace(R)-1)/2  and  R - R^t = 2*sin(A)*P
    //
    // In the event that A = pi, R-R^t = 0 which prevents us from extracting
    // the axis through P.  Instead note that R = I+2*P^2 when A = pi, so
    // P^2 = (R-I)/2.  The diagonal entries of P^2 are x^2-1, y^2-1, and
    // z^2-1.  We can solve these for axis (x,y,z).  Because the angle is pi,
    // it does not matter which sign you choose on the square roots.
    
    float fTrace = elt[0][0] + elt[1][1] + elt[2][2];
    float fCos = 0.5f * (fTrace - 1.0f);
    rfRadians = acos(fCos);  // in [0,PI]
    
    if ( rfRadians > 0.0 ) {
        if ( rfRadians < M_PI ) {
            rkAxis.X = elt[2][1] - elt[1][2];
            rkAxis.Y = elt[0][2] - elt[2][0];
            rkAxis.Z = elt[1][0] - elt[0][1];
            rkAxis = rkAxis.direction();
        } else {
            // angle is PI
            float fHalfInverse;
            
            if ( elt[0][0] >= elt[1][1] ) {
                // r00 >= r11
                if ( elt[0][0] >= elt[2][2] ) {
                    // r00 is maximum diagonal term
                    rkAxis.Y = 0.5 * sqrt(elt[0][0] -
                                          elt[1][1] - elt[2][2] + 1.0);
                    fHalfInverse = 0.5 / rkAxis.X;
                    rkAxis.Y = fHalfInverse * elt[0][1];
                    rkAxis.Z = fHalfInverse * elt[0][2];
                } else {
                    // r22 is maximum diagonal term
                    rkAxis.Z = 0.5 * sqrt(elt[2][2] -
                                          elt[0][0] - elt[1][1] + 1.0);
                    fHalfInverse = 0.5 / rkAxis.Z;
                    rkAxis.X = fHalfInverse * elt[0][2];
                    rkAxis.Y = fHalfInverse * elt[1][2];
                }
            } else {
                // r11 > r00
                if ( elt[1][1] >= elt[2][2] ) {
                    // r11 is maximum diagonal term
                    rkAxis.Y = 0.5 * sqrt(elt[1][1] -
                                          elt[0][0] - elt[2][2] + 1.0);
                    fHalfInverse = 0.5 / rkAxis.Y;
                    rkAxis.X = fHalfInverse * elt[0][1];
                    rkAxis.Z = fHalfInverse * elt[1][2];
                } else {
                    // r22 is maximum diagonal term
                    rkAxis.Z = 0.5 * sqrt(elt[2][2] -
                                          elt[0][0] - elt[1][1] + 1.0);
                    fHalfInverse = 0.5 / rkAxis.Z;
                    rkAxis.X = fHalfInverse * elt[0][2];
                    rkAxis.Y = fHalfInverse * elt[1][2];
                }
            }
        }
    } else {
        // The angle is 0 and the matrix is the identity.  Any axis will
        // work, so just use the x-axis.
        rkAxis.X = 1.0;
        rkAxis.Y = 0.0;
        rkAxis.Z = 0.0;
    }
}

//----------------------------------------------------------------------------
Matrix3 Matrix3::fromAxisAngle (const Vector3& _axis, float fRadians) {
    return fromUnitAxisAngle(_axis.direction(), fRadians);
}

Matrix3 Matrix3::fromUnitAxisAngle (const Vector3& axis, float fRadians) {

	Matrix3 m;
    float fCos  = cos(fRadians);
    float fSin  = sin(fRadians);
    float fOneMinusCos = 1.0 - fCos;
    float fX2   = (axis.X)*(axis.X);
    float fY2   = (axis.Y)*(axis.Y);
    float fZ2   = (axis.Z)*(axis.Z);
    float fXYM  = axis.X * axis.Y * fOneMinusCos;
    float fXZM  = axis.X * axis.Z * fOneMinusCos;
    float fYZM  = axis.Y * axis.Z * fOneMinusCos;
    float fXSin = axis.X * fSin;
    float fYSin = axis.Y * fSin;
    float fZSin = axis.Z * fSin;
    
    m.elt[0][0] = fX2 * fOneMinusCos + fCos;
    m.elt[0][1] = fXYM - fZSin;
    m.elt[0][2] = fXZM + fYSin;
    
    m.elt[1][0] = fXYM + fZSin;
    m.elt[1][1] = fY2 * fOneMinusCos + fCos;
    m.elt[1][2] = fYZM - fXSin;
    
    m.elt[2][0] = fXZM - fYSin;
    m.elt[2][1] = fYZM + fXSin;
    m.elt[2][2] = fZ2 * fOneMinusCos + fCos;
    
    return m;
}

//----------------------------------------------------------------------------
bool Matrix3::toEulerAnglesXYZ (float& rfXAngle, float& rfYAngle,
                                float& rfZAngle) const {
    // rot =  cy*cz          -cy*sz           sy
    //        cz*sx*sy+cx*sz  cx*cz-sx*sy*sz -cy*sx
    //       -cx*cz*sy+sx*sz  cz*sx+cx*sy*sz  cx*cy
    
    if ( elt[0][2] < 1.0f ) {
        if ( elt[0][2] > -1.0f ) {
            rfXAngle = atan2( -elt[1][2], elt[2][2]);
            rfYAngle = (float) asin(elt[0][2]);
            rfZAngle = atan2( -elt[0][1], elt[0][0]);
            return true;
        } else {
            // WARNING.  Not unique.  XA - ZA = -atan2(r10,r11)
            rfXAngle = -atan2(elt[1][0], elt[1][1]);
            rfYAngle = -(float)M_PI_2;
            rfZAngle = 0.0f;
            return false;
        }
    } else {
        // WARNING.  Not unique.  XAngle + ZAngle = atan2(r10,r11)
        rfXAngle = atan2(elt[1][0], elt[1][1]);
        rfYAngle = (float)M_PI_2;
        rfZAngle = 0.0f;
        return false;
    }
}

//----------------------------------------------------------------------------
bool Matrix3::toEulerAnglesXZY (float& rfXAngle, float& rfZAngle,
                                float& rfYAngle) const {
    // rot =  cy*cz          -sz              cz*sy
    //        sx*sy+cx*cy*sz  cx*cz          -cy*sx+cx*sy*sz
    //       -cx*sy+cy*sx*sz  cz*sx           cx*cy+sx*sy*sz
    
    if ( elt[0][1] < 1.0f ) {
        if ( elt[0][1] > -1.0f ) {
            rfXAngle = atan2(elt[2][1], elt[1][1]);
            rfZAngle = (float) asin( -elt[0][1]);
            rfYAngle = atan2(elt[0][2], elt[0][0]);
            return true;
        } else {
            // WARNING.  Not unique.  XA - YA = atan2(r20,r22)
            rfXAngle = atan2(elt[2][0], elt[2][2]);
            rfZAngle = (float)M_PI_2;
            rfYAngle = 0.0;
            return false;
        }
    } else {
        // WARNING.  Not unique.  XA + YA = atan2(-r20,r22)
        rfXAngle = atan2( -elt[2][0], elt[2][2]);
        rfZAngle = -(float)M_PI_2;
        rfYAngle = 0.0f;
        return false;
    }
}

//----------------------------------------------------------------------------
bool Matrix3::toEulerAnglesYXZ (float& rfYAngle, float& rfXAngle,
                                float& rfZAngle) const {
    // rot =  cy*cz+sx*sy*sz  cz*sx*sy-cy*sz  cx*sy
    //        cx*sz           cx*cz          -sx
    //       -cz*sy+cy*sx*sz  cy*cz*sx+sy*sz  cx*cy
    
    if ( elt[1][2] < 1.0 ) {
        if ( elt[1][2] > -1.0 ) {
            rfYAngle = atan2(elt[0][2], elt[2][2]);
            rfXAngle = (float) asin( -elt[1][2]);
            rfZAngle = atan2(elt[1][0], elt[1][1]);
            return true;
        } else {
            // WARNING.  Not unique.  YA - ZA = atan2(r01,r00)
            rfYAngle = atan2(elt[0][1], elt[0][0]);
            rfXAngle = (float)M_PI_2;
            rfZAngle = 0.0;
            return false;
        }
    } else {
        // WARNING.  Not unique.  YA + ZA = atan2(-r01,r00)
        rfYAngle = atan2( -elt[0][1], elt[0][0]);
        rfXAngle = -(float)M_PI_2;
        rfZAngle = 0.0f;
        return false;
    }
}

//----------------------------------------------------------------------------
bool Matrix3::toEulerAnglesYZX (float& rfYAngle, float& rfZAngle,
                                float& rfXAngle) const {
    // rot =  cy*cz           sx*sy-cx*cy*sz  cx*sy+cy*sx*sz
    //        sz              cx*cz          -cz*sx
    //       -cz*sy           cy*sx+cx*sy*sz  cx*cy-sx*sy*sz
    
    if ( elt[1][0] < 1.0 ) {
        if ( elt[1][0] > -1.0 ) {
            rfYAngle = atan2( -elt[2][0], elt[0][0]);
            rfZAngle = (float) asin(elt[1][0]);
            rfXAngle = atan2( -elt[1][2], elt[1][1]);
            return true;
        } else {
            // WARNING.  Not unique.  YA - XA = -atan2(r21,r22);
            rfYAngle = -atan2(elt[2][1], elt[2][2]);
            rfZAngle = -(float)M_PI_2;
            rfXAngle = 0.0;
            return false;
        }
    } else {
        // WARNING.  Not unique.  YA + XA = atan2(r21,r22)
        rfYAngle = atan2(elt[2][1], elt[2][2]);
        rfZAngle = (float)M_PI_2;
        rfXAngle = 0.0f;
        return false;
    }
}

//----------------------------------------------------------------------------
bool Matrix3::toEulerAnglesZXY (float& rfZAngle, float& rfXAngle,
                                float& rfYAngle) const {
    // rot =  cy*cz-sx*sy*sz -cx*sz           cz*sy+cy*sx*sz
    //        cz*sx*sy+cy*sz  cx*cz          -cy*cz*sx+sy*sz
    //       -cx*sy           sx              cx*cy
    
    if ( elt[2][1] < 1.0 ) {
        if ( elt[2][1] > -1.0 ) {
            rfZAngle = atan2( -elt[0][1], elt[1][1]);
            rfXAngle = (float) asin(elt[2][1]);
            rfYAngle = atan2( -elt[2][0], elt[2][2]);
            return true;
        } else {
            // WARNING.  Not unique.  ZA - YA = -atan(r02,r00)
            rfZAngle = -atan2(elt[0][2], elt[0][0]);
            rfXAngle = -(float)M_PI_2;
            rfYAngle = 0.0f;
            return false;
        }
    } else {
        // WARNING.  Not unique.  ZA + YA = atan2(r02,r00)
        rfZAngle = atan2(elt[0][2], elt[0][0]);
        rfXAngle = (float)M_PI_2;
        rfYAngle = 0.0f;
        return false;
    }
}

//----------------------------------------------------------------------------
bool Matrix3::toEulerAnglesZYX (float& rfZAngle, float& rfYAngle,
                                float& rfXAngle) const {
    // rot =  cy*cz           cz*sx*sy-cx*sz  cx*cz*sy+sx*sz
    //        cy*sz           cx*cz+sx*sy*sz -cz*sx+cx*sy*sz
    //       -sy              cy*sx           cx*cy
    
    if ( elt[2][0] < 1.0 ) {
        if ( elt[2][0] > -1.0 ) {
            rfZAngle = atan2f(elt[1][0], elt[0][0]);
            rfYAngle = asinf(-(double)elt[2][1]);
            rfXAngle = atan2f(elt[2][1], elt[2][2]);
            return true;
        } else {
            // WARNING.  Not unique.  ZA - XA = -atan2(r01,r02)
            rfZAngle = -atan2(elt[0][1], elt[0][2]);
            rfYAngle = (float)M_PI_2;
            rfXAngle = 0.0f;
            return false;
        }
    } else {
        // WARNING.  Not unique.  ZA + XA = atan2(-r01,-r02)
        rfZAngle = atan2( -elt[0][1], -elt[0][2]);
        rfYAngle = -(float)M_PI_2;
        rfXAngle = 0.0f;
        return false;
    }
}

//----------------------------------------------------------------------------
Matrix3 Matrix3::fromEulerAnglesXYZ (float fYAngle, float fPAngle,
                                     float fRAngle) {
    float fCos, fSin;
    
    fCos = cosf(fYAngle);
    fSin = sinf(fYAngle);
    Matrix3 kXMat(1.0f, 0.0f, 0.0f, 0.0f, fCos, -fSin, 0.0, fSin, fCos);
    
    fCos = cosf(fPAngle);
    fSin = sinf(fPAngle);
    Matrix3 kYMat(fCos, 0.0f, fSin, 0.0f, 1.0f, 0.0f, -fSin, 0.0f, fCos);
    
    fCos = cosf(fRAngle);
    fSin = sinf(fRAngle);
    Matrix3 kZMat(fCos, -fSin, 0.0f, fSin, fCos, 0.0f, 0.0f, 0.0f, 1.0f);
    
    return kXMat * (kYMat * kZMat);
}

//----------------------------------------------------------------------------
Matrix3 Matrix3::fromEulerAnglesXZY (float fYAngle, float fPAngle,
                                     float fRAngle) {
    
    float fCos, fSin;
    
    fCos = cosf(fYAngle);
    fSin = sinf(fYAngle);
    Matrix3 kXMat(1.0, 0.0, 0.0, 0.0, fCos, -fSin, 0.0, fSin, fCos);
    
    fCos = cosf(fPAngle);
    fSin = sinf(fPAngle);
    Matrix3 kZMat(fCos, -fSin, 0.0, fSin, fCos, 0.0, 0.0, 0.0, 1.0);
    
    fCos = cosf(fRAngle);
    fSin = sinf(fRAngle);
    Matrix3 kYMat(fCos, 0.0, fSin, 0.0, 1.0, 0.0, -fSin, 0.0, fCos);
    
    return kXMat * (kZMat * kYMat);
}

//----------------------------------------------------------------------------
Matrix3 Matrix3::fromEulerAnglesYXZ(
                                    float fYAngle, 
                                    float fPAngle,
                                    float fRAngle) {
    
    float fCos, fSin;
    
    fCos = cos(fYAngle);
    fSin = sin(fYAngle);
    Matrix3 kYMat(fCos, 0.0f, fSin, 0.0f, 1.0f, 0.0f, -fSin, 0.0f, fCos);
    
    fCos = cos(fPAngle);
    fSin = sin(fPAngle);
    Matrix3 kXMat(1.0f, 0.0f, 0.0f, 0.0f, fCos, -fSin, 0.0f, fSin, fCos);
    
    fCos = cos(fRAngle);
    fSin = sin(fRAngle);
    Matrix3 kZMat(fCos, -fSin, 0.0f, fSin, fCos, 0.0f, 0.0f, 0.0f, 1.0f);
    
    return kYMat * (kXMat * kZMat);
}

//----------------------------------------------------------------------------
Matrix3 Matrix3::fromEulerAnglesYZX(
                                    float fYAngle, 
                                    float fPAngle,
                                    float fRAngle) {
    
    float fCos, fSin;
    
    fCos = cos(fYAngle);
    fSin = sin(fYAngle);
    Matrix3 kYMat(fCos, 0.0f, fSin, 0.0f, 1.0f, 0.0f, -fSin, 0.0f, fCos);
    
    fCos = cos(fPAngle);
    fSin = sin(fPAngle);
    Matrix3 kZMat(fCos, -fSin, 0.0f, fSin, fCos, 0.0f, 0.0f, 0.0f, 1.0f);
    
    fCos = cos(fRAngle);
    fSin = sin(fRAngle);
    Matrix3 kXMat(1.0f, 0.0f, 0.0f, 0.0f, fCos, -fSin, 0.0f, fSin, fCos);
    
    return kYMat * (kZMat * kXMat);
}

//----------------------------------------------------------------------------
Matrix3 Matrix3::fromEulerAnglesZXY (float fYAngle, float fPAngle,
                                     float fRAngle) {
    float fCos, fSin;
    
    fCos = cos(fYAngle);
    fSin = sin(fYAngle);
    Matrix3 kZMat(fCos, -fSin, 0.0, fSin, fCos, 0.0, 0.0, 0.0, 1.0);
    
    fCos = cos(fPAngle);
    fSin = sin(fPAngle);
    Matrix3 kXMat(1.0, 0.0, 0.0, 0.0, fCos, -fSin, 0.0, fSin, fCos);
    
    fCos = cos(fRAngle);
    fSin = sin(fRAngle);
    Matrix3 kYMat(fCos, 0.0, fSin, 0.0, 1.0, 0.0, -fSin, 0.0, fCos);
    
    return kZMat * (kXMat * kYMat);
}

//----------------------------------------------------------------------------
Matrix3 Matrix3::fromEulerAnglesZYX (float fYAngle, float fPAngle,
                                     float fRAngle) {
    float fCos, fSin;
    
    fCos = cos(fYAngle);
    fSin = sin(fYAngle);
    Matrix3 kZMat(fCos, -fSin, 0.0, fSin, fCos, 0.0, 0.0, 0.0, 1.0);
    
    fCos = cos(fPAngle);
    fSin = sin(fPAngle);
    Matrix3 kYMat(fCos, 0.0, fSin, 0.0, 1.0, 0.0, -fSin, 0.0, fCos);
    
    fCos = cos(fRAngle);
    fSin = sin(fRAngle);
    Matrix3 kXMat(1.0, 0.0, 0.0, 0.0, fCos, -fSin, 0.0, fSin, fCos);
    
    return kZMat * (kYMat * kXMat);
}
