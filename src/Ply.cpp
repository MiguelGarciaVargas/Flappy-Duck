#include "../include/Ply.h"

Ply::Ply(string fname, float r, float g, float b) : Object(fname,r,g,b)
{
    this->load();
    this->setData();
    //this->imprimir();   //Descomentar para imprimir todas las caras->aristas->vertices
}

void Ply::load() {
    string line;
    ifstream OBJfile(fname);

    bool headerEnded = false;
    int vertexLim;
    int vertex_i = 1;

    while (getline(OBJfile, line))
    {
        vector<string> elems = this->split(line, " ");

        if (!elems.empty())
        {
            if (elems[0] == "element")
            {
                if (elems[1] == "vertex")
                {
                    vertexLim = stof(elems[2]);
                }
            }

            if (headerEnded == true)
            {
                if (vertex_i <= vertexLim)
                {
                    // Se guardan vertices  listo, no hay mas de 3 vertices
                    float x = stof(elems[0]);
                    float y = stof(elems[1]);
                    float z = stof(elems[2]);
                    Vertex v(x, y, z);
                    ListaVertices.push_back(v);
                    this->box.update(glm::vec3(v.getX(), v.getY(), v.getZ()));
    
                }
                else
                {
                    // Se generan las aristas y la cara
                    vector<int> verticesTemp;
                    for (int i = 1; i <= stof(elems[0]); i++)
                    {
                        unsigned int vi = stof(elems[i]);
                        verticesTemp.push_back(vi);
                    }

                    vector<Edge> edgesTemp;
                    for (long long unsigned int i = 0; i < stof(elems[0]) - 1; i++)
                    {
                        Edge ei(ListaVertices[verticesTemp[i]], ListaVertices[verticesTemp[i + 1]]);
                        edgesTemp.push_back(ei);
                    }
                    Edge ei(ListaVertices[verticesTemp[0]], ListaVertices[verticesTemp[stof(elems[0]) - 1]]);
                    edgesTemp.push_back(ei);

                    Face f(edgesTemp);
                    ListaCaras.push_back(f);
                }

                vertex_i++;
            }

            if (elems[0] == "end_header")
            {
                headerEnded = true;
            }
        }
    }
    
    // this->calculateBoundariesBox();
}


