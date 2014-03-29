#include "matrix4.h"

// constructors 
Matrix4::Matrix4(float r1c1, float r1c2, float r1c3, float r1c4,
                 float r2c1, float r2c2, float r2c3, float r2c4,
                 float r3c1, float r3c2, float r3c3, float r3c4,
                 float r4c1, float r4c2, float r4c3, float r4c4) {

    set(r1c1, r1c2, r1c3, r1c4, r2c1, r2c2, r2c3, r2c4, r3c1, r3c2, r3c3, r3c4, r4c1, r4c2, r4c3, r4c4);
}

// special matrices

const Matrix4& Matrix4::zero() {
    static Matrix4 m(0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0);
    return m;
}

const Matrix4& Matrix4::identity() {
    static Matrix4 m(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
    return m;
}

void Matrix4::set (float r1c1, float r1c2, float r1c3, float r1c4,
                   float r2c1, float r2c2, float r2c3, float r2c4,
                   float r3c1, float r3c2, float r3c3, float r3c4,
                   float r4c1, float r4c2, float r4c3, float r4c4) {

    elt[0][0] = r1c1;   elt[0][1] = r1c2;   elt[0][2] = r1c3;   elt[0][3] = r1c3;
    elt[1][0] = r2c1;   elt[1][1] = r2c2;   elt[1][2] = r2c3;   elt[1][3] = r2c3;
    elt[2][0] = r3c1;   elt[2][1] = r3c2;   elt[2][2] = r3c3;   elt[2][3] = r3c3;
    elt[3][0] = r4c1;   elt[3][1] = r4c2;   elt[3][2] = r4c3;   elt[3][3] = r4c4;
}

Matrix4::Matrix4(const Matrix3& upper3x3, const Vector3& lastCol) {

    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            elt[r][c] = upper3x3[r][c];
        }
        elt[r][3] = lastCol[r];
    }
    elt[3][0] = 0.0f;
    elt[3][1] = 0.0f;
    elt[3][2] = 0.0f;
    elt[3][3] = 1.0f;
}

Matrix4 Matrix4::transpose() const {
    Matrix4 result;
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            result.elt[c][r] = elt[r][c];
        }
    }
    
    return result;
}

float Matrix4::determinant() const {
    // Determinant is the dot product of the first row and the first row
    // of cofactors (i.e. the first col of the adjoint matrix)
	return cofactor().row(0).dot(row(0));
}

Matrix4 Matrix4::adjoint() const {
    return cofactor().transpose();
}

Matrix4 Matrix4::inverse() const {
    // Inverse = adjoint / determinant
    
    Matrix4 A = adjoint();
    
    // Determinant is the dot product of the first row and the first row
    // of cofactors (i.e. the first col of the adjoint matrix)
	float det = A.column(0).dot(row(0));
    
	return A * (1.0f / det);
}

Matrix4 Matrix4::cofactor() const {
	Matrix4 out;
    
    // We'll use i to incrementally compute -1 ^ (r+c)
    int i = 1;
    
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            // Compute the determinant of the 3x3 submatrix
            float det = subDeterminant(r, c);
            out.elt[r][c] = i * det;
            i = -i;
        }
        i = -i;
    }
    
    return out;
}


float Matrix4::subDeterminant(int excludeRow, int excludeCol) const {
    // Compute non-excluded row and column indices
    int row[3];
    int col[3];
    
    for (int i = 0; i < 3; ++i) {
        row[i] = i;
        col[i] = i;
        
        if (i >= excludeRow) {
            ++row[i];
        }
        if (i >= excludeCol) {
            ++col[i];
        }
    }
    
    // Compute the first row of cofactors 
    float cofactor00 = 
    elt[row[1]][col[1]] * elt[row[2]][col[2]] -
    elt[row[1]][col[2]] * elt[row[2]][col[1]];
    
    float cofactor10 = 
    elt[row[1]][col[2]] * elt[row[2]][col[0]] -
    elt[row[1]][col[0]] * elt[row[2]][col[2]];
    
    float cofactor20 = 
    elt[row[1]][col[0]] * elt[row[2]][col[1]] -
    elt[row[1]][col[1]] * elt[row[2]][col[0]];
    
    // Product of the first row and the cofactors along the first row
    return
    elt[row[0]][col[0]] * cofactor00 +
    elt[row[0]][col[1]] * cofactor10 +
    elt[row[0]][col[2]] * cofactor20;
}

const Vector4& Matrix4::row(int r) const {
    return reinterpret_cast<const Vector4*>(elt[r])[0];
}


Vector4 Matrix4::column(int c) const {
    Vector4 v;
    for (int r = 0; r < 4; ++r) {
        v[r] = elt[r][c];
    }
    return v;
}

Vector3 Matrix4::homoMul(const class Vector3& v, float w) const {
    Vector4 r = (*this) * Vector4(v, w);
    return r.xyz() * (1.0f / r.w);
}

Matrix4 Matrix4::operator*(const float s) const {
    Matrix4 result;
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            result.elt[r][c] = elt[r][c] * s;
        }
    }
    
    return result;
}

Vector4 Matrix4::operator*(const Vector4& vector) const {
    Vector4 result(0,0,0,0);
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            result[r] += elt[r][c] * vector[c];
        }
    }
    
    return result;
}
