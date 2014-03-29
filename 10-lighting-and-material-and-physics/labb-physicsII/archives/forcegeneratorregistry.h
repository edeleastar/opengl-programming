#pragma once

#include "libs.h"
#include "forcegenerators.h"

class ForceGeneratorRegistry {
protected:
    
    // Structure to keep track of a PhysicsActor<->ForceGenerator pair.
    struct Entry {
        PhysicsActor * physicsActor;
        ForceGenerator * forceGenerator;
    
    
        Entry (PhysicsActor * physicsActor, ForceGenerator * forceGenerator) 
            : physicsActor(physicsActor), forceGenerator(forceGenerator) { };
        ;
    };
                  
    typedef std::vector<Entry> Registry;
    Registry registry;
    
public:
    ForceGeneratorRegistry () : registry() {}
    
	/// Register the given PhysicsActor and ForceGenerator pair.
    void add(PhysicsActor * physicsActor, ForceGenerator * forceGenerator);
    
	/// Tells all ForceGenerators to apply forces to associated PhysicsActors
    void applyForce(float dt);
    
};