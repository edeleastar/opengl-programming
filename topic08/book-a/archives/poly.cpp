#include "util.h"
#include "ellipse.h"
#include "rectangle.h"
#include "ref2.h"
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/ptr_container/ptr_map.hpp>
using namespace boost;

void polytest1()
{
/*
  Ellipse   e(Point (1,1), 10);
  Rectangle r(Point(2,2), 20, 10);

  Shape shapes[2];

  shapes[0] = e;
  shapes[1] = r;

  for (int i=0; i<2; i++)
  {
    shapes[i].draw();
  }*/
}

void polytest2()
{
  Shape* shapes[2];
  shapes[0] = new Ellipse(Point (1,1), 10);
  shapes[1] = new Rectangle(Point(2,2), 20, 10);

  for (int i=0; i<2; i++)
  {
    shapes[i]->draw();
  }

  foreach (Shape *s, shapes)
  {
    s->draw();
  }
}

void polytest3()
{
/*  Ellipse   e(Point (1,1), 10);
  Rectangle r(Point(2,2), 20, 10);

  list <Shape> shapeList;

  shapeList.push_back(e);
  shapeList.push_back(r);

  foreach (Shape &s, shapeList)
  {
    s.draw();
  }
  */
}

template <typename T>
struct mylist : public list<T>
{
  mylist()
  {}

  virtual ~mylist()
  {
    foreach (T &s, *this)
    {
     delete s;
    }
  }
};

void polytest4()
{
  list <Shape*> shapeList;

  shapeList.push_back(new Ellipse(Point (1,1), 10));
  shapeList.push_back(new Rectangle(Point(2,2), 20, 10));

  foreach (Shape *s, shapeList)
  {
    s->draw();
  }

  foreach (Shape *s, shapeList)
  {
   delete s;
  }
}

void polytest5()
{
  mylist <Shape*> shapeList;

  shapeList.push_back(new Ellipse(Point (1,1), 10));
  shapeList.push_back(new Rectangle(Point(2,2), 20, 10));

  foreach (Shape *s, shapeList)
  {
    s->draw();
  }
}

void polytest6()
{
  list <Ref2 <Shape> > shapeList;
  shapeList.push_back(new Ellipse(Point (1,1), 10));
  shapeList.push_back(new Rectangle(Point(2,2), 20, 10));

  foreach (Shape *s, shapeList)
  {
    s->draw();
  }
}

void polytest7()
{
  list <Ref2 <Shape> > shapeList;
  static Ellipse persistentEllipse(Point(20,20), 22);
  shapeList.push_back(&persistentEllipse);
}

void polytest8()
{
  list <Ref2 <Shape> > shapeList;
  shapeList.push_back(new Ellipse(Point(20,20), 22));
}


void polytest9()
{
  ptr_list <Shape>  shapeList;

  shapeList.push_back(new Ellipse(Point (1,1), 10));
  shapeList.push_back(new Rectangle(Point(2,2), 20, 10));

  ptr_list <Shape>::iterator i;
  for (i=shapeList.begin(); i!=shapeList.end(); i++)
    i->draw();

  foreach (Shape &s, shapeList)
  {
    s.draw();
  }
}

void polytest10()
{
  typedef ptr_map<string, Shape> ShapeMap;

  ShapeMap shapes;

  string e1name="ellipse1", r1name="rect1";

  shapes.insert(e1name, new Ellipse(Point (1,1), 10));
  shapes.insert(r1name, new Rectangle(Point(2,2), 20, 10));

  foreach (ShapeMap::value_type s, shapes)
  {
    s->second->draw();
  }

  ShapeMap::iterator it = shapes.find("ellipse1");
  if (it != shapes.end())
  {
    it->second->draw();
  }
}


