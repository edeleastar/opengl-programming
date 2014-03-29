#include "glutadapter.h"
#include "world.h"

void reshape(int w, int h)
{
  theWorld.projectors.windowReshape(w,h);
}

void renderScene(void)
{
  theWorld.render();
}

void keyboard(unsigned char key, int x, int y)
{
  theWorld.keyPress(key);
}




