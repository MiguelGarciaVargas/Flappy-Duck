#include "../include/Face.h"
#include <cmath>

using namespace std;

Face::Face(vector<Edge> edges) 
{
    this->edges = edges;
    this->normal = calcularNormal();
}

void Face::print()
{
    int i = 1;
    for (Edge e : this->edges)
    {
        cout << "Edge: " << i++ << endl;
        e.print();
        cout << endl;
    }
}

void Face::calcularPerimetro()
{
    float distanciaActual = 0;
    for (int i = 0; i < this->edges.size(); i++)
    {
        vector<float> vi = this->edges[i].getVi().getXYZ();
        vector<float> vf = this->edges[(i + 1) % this->edges.size()].getVi().getXYZ();

        distanciaActual += sqrt(pow(vi[0] - vf[0],2) + pow(vi[1] - vf[1], 2) + pow(vi[2] - vf[2], 2));

    }

    this->perimeter = distanciaActual;
}

vector<Edge> Face::getEdges(){
    return edges;
}



Vertex Face::calcularNormal() 
{
    Vertex v1 = this->edges[1].getVi() - this->edges[0].getVi();
    Vertex v2 = this->edges[2].getVi() - this->edges[0].getVi();

    // Calculamos el producto cruz de los dos vectores para obtener la normal
    float x = v1.getY() * v2.getZ() - v1.getZ() * v2.getY();
    float y = v1.getZ() * v2.getX() - v1.getX() * v2.getZ();
    float z = v1.getX() * v2.getY() - v1.getY() * v2.getX();

    //Normalizar
    float resultado = sqrt(pow(x,2) + pow(y,2) + pow(z,2));

    return Vertex(x/result,y/result,z/result);
}