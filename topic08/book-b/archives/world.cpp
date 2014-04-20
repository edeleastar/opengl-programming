#include "world.h"
#include "color.h"
#include "glutadapter.h"
#include <ctime>

using namespace std;

World* World::s_World = NULL;

World& World::GetInstance()
{
  if (s_World == NULL)
  {
    s_World = new World();
  }
  return *s_World;
}

void World::render()
{
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  foreach (GeometryMap::value_type geometry, *renderables)
  {
    geometry.second.render();
  }

  glutSwapBuffers();
}

void World::keyPress(unsigned char ch)
{
  if (ch >= '1' && ch <= '4')
  {
	projectors.keyPress(ch);
  }
  glutPostRedisplay();
}

void World::initialize(string name, int width, int height)
{
  int argc=0;
  char** argv;
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(width, height);
  glutCreateWindow(name.c_str());

  Color::Black.renderClear();
  glEnable(GL_DEPTH_TEST);
  glFrontFace(GL_CCW);
  glPolygonMode(GL_FRONT,GL_LINE);
  glPolygonMode(GL_BACK,GL_LINE);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0f, 1, 1.0, 1000.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  glutDisplayFunc(renderScene);
}

void World::start()
{
  glutMainLoop();
}

