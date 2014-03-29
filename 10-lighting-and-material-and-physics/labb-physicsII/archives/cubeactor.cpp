#include "cubeactor.h"
#include "cmath"

using namespace std;

CubeActor::CubeActor(Geometry *geometry)
: PhysicsActor(geometry)
{

    std::cout <<"Creating cube " <<geometry->name <<std::endl;
 
    // STEP 1
    //
    // Use faces/vertices geomerty to determine 
    // the shape, dimensions and position and orientation.

    position = Vector3::zero();
    unsigned int vertexCount = 0;
    foreach (Vector3 &vector, geometry->vertices)
    {
        position += vector;
        ++vertexCount;
    }
    position /= float(vertexCount);
    std::cout <<"\t Position is " <<position <<std::endl;

    // STEP 2
    //
    // Get non-geometrical settings from second data file.
    // These are hard coded here as I am lazy/Eamon is not paying enough.

    //velocity = Vector3(0,1,0);
    //acceleration = Vector3(0,-.1,0);
    inverseMass = 1.0f;
    damping = 1.0f;
    
    // STEP 3
    // Update geometry based on object physical properties
    //
    // At a minimum the vertices are given relative to the object's 
    // position and orientation.

    foreach (Vector3 &vector, geometry->vertices)
    {
        vector -= position;
    }
}

