#include "face.h"

using namespace std;

Face::Face(istream& is)
{
  string line;
  getline (is, line);

  stringstream allIndexSets (line);
  string singleIndexSet;

  while( getline(allIndexSets, singleIndexSet, ' ') )
  {
   if (singleIndexSet.size() > 0)
   {
     string vertexIndex = singleIndexSet.substr(0, singleIndexSet.find('/'));
     int index = atoi(vertexIndex.c_str());
     vertexIndices.push_back(index);
   }
  }
}

void Face::render(std::vector <Vector3>&vertexTable)
{
  vertexIndices.size() == 3?
     glBegin(GL_TRIANGLES)
    :glBegin(GL_QUADS);

  foreach (int index, vertexIndices)
  {
    glVertex3f( vertexTable[index-1].X,
                vertexTable[index-1].Y,
                vertexTable[index-1].Z );
  }
  glEnd();
}
