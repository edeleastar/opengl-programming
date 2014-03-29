#include "forcegenerators.h"

// base force generator
// --------------------------------------------------------


// nothing needed here



// specific force generators
// --------------------------------------------------------
AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(const Vector3& anchor, float springConstant, float restLength) 
    : ForceGenerator(), anchor(anchor), springConstant(springConstant), restLength(restLength) { }


void AnchoredSpringForceGenerator::applyForce(PhysicsActor * physicsActor, float dt) {
	(void) dt;
	
    // Calculate the vector of the spring
    Vector3 force = physicsActor->position - anchor;
    
    // Calculate the magnitude of the force
	float currentLength = force.length();
    float length = (currentLength - restLength)*springConstant;
    force *= (-length/currentLength) ;
    
    physicsActor->addForce(force);	
}
