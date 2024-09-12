#ifndef EDGE_H
#define EDGE_H

#pragma once

#include <iostream>
#include "../include/Vertex.h"

class Edge
{
private:
    Vertex vi, vf;

public:
    Edge(Vertex vi, Vertex vf);
    Vertex getVi();
    Vertex getVf();
    void print();
};

#endif