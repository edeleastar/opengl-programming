#include "cubeactor.h"
#include "cmath"

using namespace std;

//CubeActor::CubeActor() : AnimateActor()
//{
//  position = Vector3::zero();
//  velocity = Vector3::zero();
//  force = Vector3::zero();
//  acceleration = Vector3::zero();
//}

CubeActor::CubeActor(Geometry *geometry)
: AnimateActor(geometry)
{
  position = Vector3::zero();
  foreach (Face &face, geometry->faces)
  {
    foreach (int index, face.vertexIndices)
    {
      Vector3 vector = geometry->vertexGroup->vertices[index-1];
      position += vector;
    }
  }
  position *= 1.0f/8.0f;
  velocity = Vector3(0,1,0);
  acceleration = Vector3(0,-.1,0);
  inverseMass = 1.0f;
  damping = 1.0f;

  foreach (Face &face, geometry->faces)
  {
    foreach (int index, face.vertexIndices)
    {
      geometry->vertexGroup->vertices[index-1] -= position;
    }
  }
}

void CubeActor::integrate(float dt)
{
  // An unmovable particle has zero inverseMass.
  if (inverseMass <= 0.0f) return;

  // Work out the acceleration from the force.
  Vector3 resultingAcceleration(acceleration + force*inverseMass);

  // Update linear velocity from the acceleration.
  velocity +=  dt*resultingAcceleration;

  // Impose artificial drag.
  velocity *= pow(damping, dt);

  // Update linear position.
  position += dt*velocity;

  // Clear the forces.
  force = Vector3::zero();

  return;
};

void CubeActor::render()
{
  glPushMatrix();
    glTranslatef(position.X, position.Y, position.Z);
    Actor::render();
  glPopMatrix();
}
