#include "libopengl.h"
#include "quat.h"

using namespace std;


Quat Quat::operator*(const Quat& other) const {
    
    // Following Watt & Watt, page 360
    const Vector3& v1 = imag();
    const Vector3& v2 = other.imag();
    float          s1 = w;
    float          s2 = other.w;
    
    return Quat(s1*v2 + s2*v1 + v1.cross(v2), s1*s2 - v1.dot(v2));
}

Quat::Quat(const Matrix3& rot) {
    
    static const int plus1mod3[] = {1, 2, 0};
    
    // Find the index of the largest diagonal component
	// These ? operations hopefully compile to conditional
	// move instructions instead of branches.
    int i = (rot[1][1] > rot[0][0]) ? 1 : 0;
    i = (rot[2][2] > rot[i][i]) ? 2 : i;
    
	// Find the indices of the other elements
    int j = plus1mod3[i];
    int k = plus1mod3[j];
    
	// Index the elements of the vector part of the quaternion as a float*
    float* v = (float*)(this);
    
	// If we attempted to pre-normalize and trusted the matrix to be
	// perfectly orthonormal, the result would be:
	//
    //   double c = sqrt((rot[i][i] - (rot[j][j] + rot[k][k])) + 1.0)
    //   v[i] = -c * 0.5
    //   v[j] = -(rot[i][j] + rot[j][i]) * 0.5 / c
    //   v[k] = -(rot[i][k] + rot[k][i]) * 0.5 / c
    //   w    =  (rot[j][k] - rot[k][j]) * 0.5 / c
	//
	// Since we're going to pay the sqrt anyway, we perform a post normalization, which also
	// fixes any poorly normalized input.  Multiply all elements by 2*c in the above, giving:
    
	// nc2 = -c^2
    double nc2 = ((rot[j][j] + rot[k][k]) - rot[i][i]) - 1.0;
    v[i] =  nc2;
    w    =  (rot[j][k] - rot[k][j]);
    v[j] = -(rot[i][j] + rot[j][i]);
    v[k] = -(rot[i][k] + rot[k][i]);
    
	// We now have the correct result with the wrong magnitude, so normalize it:
    float s = sqrt(x*x + y*y + z*z + w*w);
    if (s > 0.00001f) {
	    s = 1.0f / s;
	    x *= s;
	    y *= s;
	    z *= s;
	    w *= s;
    } else {
        // The quaternion is nearly zero.  Make it 0 0 0 1
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
        w = 1.0f;
    }
}


void Quat::toAxisAngleRotation(
                               Vector3&            axis,
                               float&             angle) const {
    
    // Decompose the quaternion into an angle and an axis.
    
    axis = Vector3(x, y, z);
    angle = 2 * acos(w);
    
    float len = sqrt(1.0f - w * w);
    
    if (abs(len) > 0.1E-8f) {
        axis /= len;
    }
    
    // Reduce the range of the angle.
    
    if (angle < 0) {		
		angle = -angle;
		axis = -axis;
    }
    
	while (angle > 2.0f*M_PI) {
        angle -= 2.0f*M_PI;
    }
    
	if (abs(angle) > M_PI) {
		angle -= 2.0f*M_PI;
    }
    
    // Make the angle positive.
	if (angle < 0.0f) {		
		angle = -angle;
        axis = -axis;
	}
}

Matrix3 Quat::toRotationMatrix() const {
    Matrix3 out = Matrix3::zero();
    
    toRotationMatrix(out);
    
    return out;
}


void Quat::toRotationMatrix(Matrix3& rot) const {    
    rot = Matrix3(*this);
}


std::ostream& operator <<(std::ostream& outputStream, const Quat& q)
{
	outputStream <<"(" <<q.x <<", " <<q.y <<", " <<q.z <<", " <<q.w <<" )";
	return outputStream;
}


