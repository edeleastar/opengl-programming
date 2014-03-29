#include "scene.h"
#include "model.h"
#include "animateactor.h"
#include "cubeactor.h"

using namespace std;


Scene:: Scene(Model *model)
{
  foreach (GeometryMap::value_type &value, model->entities)
  {
    string name = value.first;
    Actor *actor;
    if (name == "cube")
    {
      actor = new CubeActor(&value.second);
      animateActors[name] = (AnimateActor*) actor;
    }
    else
    {
      actor = new Actor(&value.second);
    }
    actors.insert(name, actor);
  }
}

void Scene::render()
{
  foreach (ActorMap::value_type value, actors)
  {
    value->second->render();
  }
}

void Scene::tick(float secondsDelta)
{
  foreach (AnimateActorMap::value_type value, animateActors)
  {
    value.second->integrate(secondsDelta);
  }
}


