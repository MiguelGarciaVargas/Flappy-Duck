#include "../include/Obj.h"

Obj::Obj(string fname,float r, float g, float b) : Object(fname,r,g,b)
{
  this->load();
  this->setData();
  
  //this->imprimir();   //Descomentar para imprimir todas las caras->aristas->vertices
}

void Obj::load(){
  string line;
  ifstream OBJfile(fname);

  while (getline(OBJfile, line))
  {
    vector<string> elems = this->split(line, " ");
    if (!elems.empty())
    {
      if (elems[0] == "v")
      {
        float x = stof(elems[1]);
        float y = stof(elems[2]);
        float z = stof(elems[3]);
        Vertex v(x, y, z);
        ListaVertices.push_back(v);
        this->box.update(glm::vec3(v.getX(), v.getY(), v.getZ()));
      }

      if (elems[0] == "f")
      {
        vector<int> verticesIndices;

        for (long long unsigned int i = 1; i < elems.size(); i++)
        {
          unsigned int vi = stoi(this->split(elems[i], "/")[0]) - 1;

          verticesIndices.push_back(vi);
        }

        vector<Edge> edgesTemp;

        for (long long unsigned int i = 0; i < verticesIndices.size() - 1; i++)
        {
          Edge ei(ListaVertices[verticesIndices[i]], ListaVertices[verticesIndices[i + 1]]);
          edgesTemp.push_back(ei);
        }

        Edge ei(ListaVertices[verticesIndices[0]], ListaVertices[verticesIndices[verticesIndices.size() - 1]]);
        edgesTemp.push_back(ei);

        Face f(edgesTemp);
        ListaCaras.push_back(f);
      }
    }
  }
  
  //this->calculateBoundariesBox();
}
