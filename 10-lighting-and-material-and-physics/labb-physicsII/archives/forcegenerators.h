#pragma once

#include "physicsactor.h"

// base force generator
// --------------------------------------------------------

class ForceGenerator {
public:
    virtual void applyForce(PhysicsActor* physicsActor, float dt) = 0;
};


// specific force generators
// --------------------------------------------------------



// spring force between a anchored point and a object
// --------------------------------------------------------
class AnchoredSpringForceGenerator : public ForceGenerator {
    
private:	
	
	Vector3 anchor;             ///< Position of fixed end of spring.
	float   springConstant;		///< The sprint constant.
	float   restLength;			///< The rest length of the spring.
	
public:
	AnchoredSpringForceGenerator(const Vector3& anchor, float springConstant, float restLength);
	virtual void applyForce(PhysicsActor* physicsActor, float dt);
};