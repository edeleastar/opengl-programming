//
//  forcegeneratorregistry.cpp
//  PhysicsModel
//
//  Created by Kieran Murphy on 14/03/2012.
//  Copyright (c) 2012 WIT. All rights reserved.
//

#include "forcegeneratorregistry.h"
#include "boost/foreach.hpp"

void ForceGeneratorRegistry::add(PhysicsActor * physicsActor, ForceGenerator * forceGenerator) {

    registry.push_back(ForceGeneratorRegistry::Entry(physicsActor, forceGenerator));
}


void ForceGeneratorRegistry::applyForce(float dt) {
    
    foreach (Entry entry, registry) {
        entry.forceGenerator->applyForce(entry.physicsActor, dt);
    }
}
