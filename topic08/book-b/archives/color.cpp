#include "libopengl.h"
#include "Color.h"

Color Color::Black   (0,     0,    0);
Color Color::Blue    (0,     0,  255);
Color Color::Green   (0,   255,    0);
Color Color::Cyan    (0,   255,  255);
Color Color::Red     (255,   0,    0);
Color Color::Magenta (255,   0,  255);
Color Color::Yellow  (255, 255,    0);
Color Color::White   (255, 255,  255);


Color::Color()
{
  R = G = B = A = 1.0f;
}

Color::Color(float r, float g, float b, float a)
{
  R = r;
  G = g;
  B = b;
  A = a;
}

Color::Color(int r, int g, int b, int a)
{
  R = (float) r / 255.0f;
  G = (float) g / 255.0f;
  B = (float) b / 255.0f;
  A = (float) a / 255.0f;
}

void Color::render()
{
  glColor4f(R,G,B,A);
}

void Color::renderClear()
{
  glClearColor(R,G,B, 1.0f);
}
