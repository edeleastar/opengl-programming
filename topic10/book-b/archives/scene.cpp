#include "scene.h"
#include "model.h"
#include "animateactor.h"
#include "cubeactor.h"
#include "colourcube.h"
#include "jetplane.h"
#include "sphereactor.h"
#include "forcegeneratorregistry.h"

using namespace std;

Scene::Scene(Model *model)
{
  foreach (GeometryMap::value_type &value, model->entities)
  {
    string name = value.first;
    Actor *actor;
    std::cout << name << std::endl;

    // TODO (for you)
    // Determine physical primatives using name format pShape#
    //
    // String comparision should not include object number!!

    if (name == "pCube1")
    {
      actor = new CubeActor(&value.second);

    }
    else if (name == "pSphere1")
    {

      PhysicsActor * sphere = new SphereActor(&value.second);
      actor = dynamic_cast<Actor*>(sphere);

      // create an anchor
      Vector3 anchor = sphere->position + Vector3(0, 5, 0);
      // create force generator
      AnchoredSpringForceGenerator * fg = new AnchoredSpringForceGenerator(
        anchor, 1.0, 3.0);
      // add actor<->forceGenerator pair to registry
      forceGeneratorRegistry.add(sphere, fg);

    }
    else if (name == "pSphere2" || name == "pSphere3")
    {

      actor = new SphereActor(&value.second);

    }
    else
    {
      actor = new Actor(&value.second);
    }

    // add phhysics actors (name start wiath a 'p') to animateActors collection
    if (name[0] == 'p')
    {
      animateActors[name] = (AnimateActor*) actor;
    }

    actors.insert(name, actor);
  }
}

void
Scene::render()
{
  foreach (ActorMap::value_type value, actors)
    {
    value->second->render();
    }

  // draw grid on ground
  const float RANGE = 15.0f;
  glLineWidth(5);
  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_LINES);
  for (int i = -5; i <= 5; ++i)
  {
  float offset = 0.2 * float(i) * RANGE;
  glVertex3f(-RANGE, 0, offset);
  glVertex3f(RANGE, 0, offset);
  glVertex3f(offset, 0, -RANGE);
  glVertex3f(offset, 0, RANGE);
  }
  glEnd();
  glLineWidth(1);
}

void
Scene::tick(float secondsDelta)
{
  forceGeneratorRegistry.applyForce(secondsDelta);

  foreach (AnimateActorMap::value_type value, animateActors)
  {
    value.second->integrate(secondsDelta);
  }
}
