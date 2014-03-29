#pragma once

#include "libs.h"
#include "vector3.h"
#include "animateactor.h"
#include "matrix3.h"
#include "matrix4.h"
#include "quat.h"

/** To properly construct a phyiscs primative (Sphere,Cube, Cone etc)
 *  one needs more data than what is stored in waveform model file.
 *  Also we want to avoid storing the same data in two separate files 
 *  so the solution adopted here is:
 *
 *  1/  Calculate as much as possible from the vertex positions 
 *      in the waveform model file. This will give us shape, position, 
 *      orientation and dimensions.
 *  2/  From a second data file read in additional properties needed 
 *      for physics modelling --- damping, mass, etc
 *  3/  The name field is used to identify physics primatives using
 *      patterm pShape# where "Shape" is "Cube", "Sphere", "Cone", etc.
 *
 *  In this skeleton version of the code the data intended to be read 
 *  in from the second file is hard coded.
 */

class PhysicsActor : public AnimateActor
{
public:
    
    float       inverseMass;
    Matrix3		inverseInertiaTensor;
    
    float 		linearDamping;
	float 		angularDamping;
    
    Vector3		position;				// position in world space.
	Quat		orientation;			// orientation in world space.
	Vector3		velocity;				// velocity in world space.
	Vector3		rotation;				// rotation in world space
    
	float		motion;
	bool 		isAwake;
	bool		canSleep;
    
	// derived data 
	
	Matrix3		inverseInertiaTensorWorld;
	
	// Holds a transform matrix for converting body space into world 
	// space and vice versa. This can be achieved by calling the 
	// getPointIn*Space functions.
	Matrix4 	transformMatrix;		// (D) body space to world space.
	
    //	AABox		m_AABB;					// axis alligned bounding box
	
	// generated data during simulation
	
	Vector3		force;					// total force being applied.
	Vector3		torque;					// total torque begin applied.
	
	Vector3		acceleration;			// acceleration in world space.
	Vector3		resultantAcceleration;	// acc arising from Newton's 2nd law
    
	static const float sleepEpsilon;	// tolerrance for sleep state.
	
	bool		debug;                  // flag to control console logs
    
    /**
     *  Using the above two file system for specifing physics objects a 
     *  construcor should have the following structure:
     *  1/  The list of faces/vertices is given in geometry. Using this
     *      the shape, dimensions and position and orientation is determined.
     *  2/  Read from the second data file the non geometric properties 
     *      associated with this object.
     *  3/  Update gemoetry based on object's physical properties, ie change
     *      vertex coordinate to body coordinates.
     */
    PhysicsActor(Geometry * geometry);

    void render();
    
    // Calculates internal data (transformMatrix, ...) from state data. 
	// This should be called after the body's state is altered 
	// directly (it is called automatically during integration).
	// If the body's state is changed immediately before the 
	// integrate step, then calling this function can be omitted.
	virtual void calculateDerivedData(bool forceUpdate=false);

	void integrate(float dt);
    
    void setDamping(float linearDamping, float angularDamping);
    void setLinearDamping(float linearDamping);
	float getLinearDamping() const;
	void setAngularDamping(float angularDamping);
	float getAngularDamping() const;
    
	void setMass(float mass);
	float getMass() const;
	
	void setInverseMass(float inverseMass);
	float getInverseMass() const;
	
	bool hasFiniteMass() const;
	
	void setInertiaTensor(const Matrix3 &inertiaTensor);
	Matrix3 getInertiaTensor() const;
	
	Matrix3 getInertiaTensorWorld() const;
	
	void setInverseInertiaTensor(const Matrix3 &inverseInertiaTensor);
	Matrix3 getInverseInertiaTensor() const;
	
    Matrix3 getInverseInertiaTensorWorld() const;
    
	void setPosition(const Vector3& position);
	Vector3 getPosition() const;
    
    void setOrientation(const Quat& orientation);
	void setOrientation(float r, float i, float j, float k);
	Quat getOrientation() const;
	Matrix3 getOrientationAsRotation() const;
	
	Matrix4 getTransform() const;
    
	Vector3 getPointInLocalSpace(const Vector3& point) const;
	Vector3 getPointInWorldSpace(const Vector3& point) const;
	Vector3 getDirectionInLocalSpace(const Vector3& direction) const;
    Vector3 getDirectionInWorldSpace(const Vector3& direction) const;
    
	void setVelocity(const Vector3& velocity);
	Vector3 getVelocity() const;
	void addVelocity(const Vector3& deltaVelocity);
	
	void setRotation(const Vector3& rotation);
	Vector3 getRotation() const;
	void addRotation(const Vector3& deltaRotation);
    
	bool getAwake() const { return isAwake; }
	void setAwake(const bool value=true);
	bool getCanSleep() const { return canSleep; }
	void setCanSleep(const bool value=true);
	
	void addForce(const Vector3& force);
	
	void addForceAtPoint(const Vector3& force, const Vector3& point);
    void addForceAtBodyPoint(const Vector3& force, const Vector3& point);
    
	void addTorque(const Vector3& torque);
	
    Vector3 getLastFrameAcceleration() const;
    
	void setAcceleration(const Vector3& acceleration);
	Vector3 getAcceleration() const;
    
    /// to go stuff
    float damping;

};
