#include "../include/Edge.h"

using namespace std;

Edge::Edge(Vertex vi, Vertex vf)
{
    this->vi = vi;
    this->vf = vf;
}

Vertex Edge::getVi()
{
    return this->vi;
}

Vertex Edge::getVf()
{
    return this->vf;
}

void Edge::print()
{
    cout << "vi ";
    vi.print();
    cout << "vf: ";
    vf.print();
}
