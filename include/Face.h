#ifndef FACE_H
#define FACE_H

#pragma once

#include "../include/Edge.h"
#include <vector>

using namespace std;

class Face
{
private:
    vector<Edge> edges;
    Vertex normal;
    float perimeter;
    void calcularPerimetro();
    Vertex calcularNormal();

public:
    Face(vector<Edge> edges);
    void print();
    vector<Edge> getEdges();
};

#endif