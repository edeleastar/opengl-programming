#include "PhysicsActor.h"
#include "cmath"
#include <cfloat>

using namespace std;

PhysicsActor::PhysicsActor(Geometry *geometry) : 
    AnimateActor(geometry),
    inverseMass(1.0f),
    inverseInertiaTensor(Matrix3::identity()),
    linearDamping(0.97f),
    angularDamping(0.97f),
    position(Vector3::zero()),
    orientation(),
    velocity(Vector3::zero()),
    rotation(Vector3::zero()),
    motion(1.0f),
    isAwake(true),
    canSleep(true),
    inverseInertiaTensorWorld(Matrix3::identity()),
    transformMatrix(Matrix4::identity()),
    force(Vector3::zero()),
    torque(Vector3::zero()),
    acceleration(Vector3::zero()),
    resultantAcceleration(Vector3::zero()),
    debug(false)
{};

void PhysicsActor::render()
{
    glPushMatrix();
    glTranslatef(position.X, position.Y, position.Z);
    Actor::render();
    glPopMatrix();
}

const float PhysicsActor::sleepEpsilon(1.0e-4f);

void PhysicsActor::calculateDerivedData(bool forceUpdate) {
    
	orientation.unitize();
	Matrix3 r = orientation.toRotationMatrix();
	
	// Calculate the transform matrix for the body.
	transformMatrix = Matrix4 (r, position);
	
	// Calculate the inertiaTensor in world space.
	inverseInertiaTensorWorld = r * inverseInertiaTensor * r.transpose();
	
//	m_AABB = AABox(position-Vector3(1.0f,1.0f,1.0f),position+Vector3(1.0f,1.0f,1.0f));
}


void PhysicsActor::integrate(float dt) {
    
	if (!isAwake) return;
    
 	// Calculate linear acceleration from force inputs.
    resultantAcceleration = acceleration + inverseMass*force;
    
    // Calculate angular acceleration from torque inputs.
    Vector3 angularAcceleration = inverseInertiaTensorWorld*torque;
	
    // Adjust velocities
    
    // Update linear velocity from both acceleration and impulse.
    velocity += dt*resultantAcceleration;
    
    // Update angular velocity from both acceleration and impulse.
    rotation += dt*angularAcceleration;
    
    // Impose drag.
    velocity *= pow(linearDamping, dt);
    rotation *= pow(angularDamping, dt);

//    std::cout <<dt <<" " <<resultantAcceleration <<" " <<velocity <<std::endl;

//	std::cout <<dt <<" " <<angularAcceleration <<" " <<rotation <<std::endl;
    
    // Adjust positions
    
    // Update linear position.
    position += dt*velocity;
    
    // Update angular position.
    orientation += 0.5f*Quat(dt*rotation, 0.0f)*orientation;
    
    // Impose drag.
    //   velocity *= pow(linearDamping, dt);
    //   rotation *= pow(angularDamping, dt);
    
    // Normalise the orientation, and update the matrices with the new
    // position and orientation
    calculateDerivedData();
    
	// Clear accumulators.
    force = Vector3::zero();
    torque = Vector3::zero();
    
    // Update the kinetic energy store, and possibly put the body to
    // sleep.
    if (canSleep) {
        float currentMotion = velocity.lengthSqr() + rotation.lengthSqr();
        
        float bias = pow(0.5f, dt);
        motion = bias*motion + (1-bias)*currentMotion;
        
        if (motion < sleepEpsilon) {
			setAwake(false);
        } else if (motion > 10 * sleepEpsilon) {
			motion = 10 * sleepEpsilon;
		}
    }
}


void PhysicsActor::setMass(float mass) {
    inverseMass = 1.0f/mass;
}


float PhysicsActor::getMass() const {
    if (inverseMass == 0) {
        return FLT_MAX;
    } else {
        return 1.0f/inverseMass;
    }
}

void PhysicsActor::setInverseMass(float inverseMass) {
    PhysicsActor::inverseMass = inverseMass;
}
float PhysicsActor::getInverseMass() const {
    return inverseMass;
}

bool PhysicsActor::hasFiniteMass() const {
    return inverseMass > 0.0f;
}


void PhysicsActor::setInertiaTensor(const Matrix3 &inertiaTensor) {
    inverseInertiaTensor = inertiaTensor.inverse();
}
Matrix3 PhysicsActor::getInertiaTensor() const {
	return inverseInertiaTensor.inverse();
}
Matrix3 PhysicsActor::getInertiaTensorWorld() const {
	return inverseInertiaTensorWorld.inverse();
}

void PhysicsActor::setInverseInertiaTensor(const Matrix3 &inverseInertiaTensor) {
	PhysicsActor::inverseInertiaTensor = inverseInertiaTensor;
}
Matrix3 PhysicsActor::getInverseInertiaTensor() const {
	return inverseInertiaTensor;
}
Matrix3 PhysicsActor::getInverseInertiaTensorWorld() const {
	return inverseInertiaTensorWorld;
}


void PhysicsActor::setDamping(float linearDamping,float angularDamping) {
    PhysicsActor::linearDamping = linearDamping;
    PhysicsActor::angularDamping = angularDamping;
}
void PhysicsActor::setLinearDamping(float linearDamping) {
    PhysicsActor::linearDamping = linearDamping;
}
float PhysicsActor::getLinearDamping() const {
    return linearDamping;
}
void PhysicsActor::setAngularDamping(float angularDamping) {
    PhysicsActor::angularDamping = angularDamping;
}

float PhysicsActor::getAngularDamping() const {
    return angularDamping;
}


void PhysicsActor::setPosition(const Vector3& position) {
    PhysicsActor::position = position;
}
Vector3 PhysicsActor::getPosition() const {
    return position;
}

void PhysicsActor::setOrientation(const Quat& orientation) {
    PhysicsActor::orientation = orientation.toUnit();
}
Quat PhysicsActor::getOrientation() const {
    return orientation;
}
Matrix3 PhysicsActor::getOrientationAsRotation() const {
	return orientation.toRotationMatrix();
}

Matrix4 PhysicsActor::getTransform() const {
	return transformMatrix;
}

Vector3 PhysicsActor::getPointInLocalSpace(const Vector3& point) const {
	return transformMatrix.inverse().homoMul(point, 1.0f);
}

Vector3 PhysicsActor::getPointInWorldSpace(const Vector3& point) const {
    return transformMatrix.homoMul(point, 1.0f);
}


Vector3 PhysicsActor::getDirectionInLocalSpace(const Vector3 &direction) const {
    return transformMatrix.inverse().homoMul(direction, 0.0f);
}

Vector3 PhysicsActor::getDirectionInWorldSpace(const Vector3 &direction) const {
    return transformMatrix.homoMul(direction, 0.0f);
}


void PhysicsActor::setVelocity(const Vector3& velocity) {
    PhysicsActor::velocity = velocity;
}


Vector3 PhysicsActor::getVelocity() const {
    return velocity;
}

void PhysicsActor::addVelocity(const Vector3& deltaVelocity) {
    velocity += deltaVelocity;
}

void PhysicsActor::setRotation(const Vector3& rotation) {
    PhysicsActor::rotation = rotation;
}

Vector3 PhysicsActor::getRotation() const {
    return rotation;
}

void PhysicsActor::addRotation(const Vector3& deltaRotation) {
    rotation += deltaRotation;
}

void PhysicsActor::setAwake(const bool awake) {
    if (awake) {
        isAwake= true;
        // Add a bit of motion to avoid it falling asleep immediately.
        motion = sleepEpsilon*2.0f;
    } else {
        isAwake = false;
        velocity = Vector3::zero();
        rotation = Vector3::zero();
    }
}


void PhysicsActor::setCanSleep(const bool canSleep) {
    PhysicsActor::canSleep = canSleep;
    
    if (!canSleep && !isAwake) setAwake(true);
}


Vector3 PhysicsActor::getLastFrameAcceleration() const {
    return resultantAcceleration;
}


void PhysicsActor::addForce(const Vector3& force)
{
    PhysicsActor::force += force;
    isAwake = true;
}


void PhysicsActor::addForceAtBodyPoint(const Vector3& force, const Vector3& point) {
    // Convert to coordinates relative to center of mass.
    Vector3 pt = getPointInWorldSpace(point);
    addForceAtPoint(force, pt);
    isAwake = true;
}


void PhysicsActor::addForceAtPoint(const Vector3& force, const Vector3& point) {
    // Convert to coordinates relative to center of mass.
    Vector3 pt(point-position);
    
    PhysicsActor::force += force;
    PhysicsActor::torque += cross(pt,force);
    
    isAwake = true;
}

void PhysicsActor::addTorque(const Vector3 &torque)
{
    PhysicsActor::torque += torque;
    isAwake = true;
}

void PhysicsActor::setAcceleration(const Vector3 &acceleration) {
    PhysicsActor::acceleration = acceleration;
}


Vector3 PhysicsActor::getAcceleration() const {
    return acceleration;
}






