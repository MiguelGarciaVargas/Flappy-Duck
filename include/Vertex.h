#ifndef VERTEX_H
#define VERTEX_H

#pragma once

#include <vector>
#include <armadillo>

using namespace std;

class Vertex
{
private:
    float x, y, z;

public:
    Vertex();
    Vertex(float x, float y, float z); 
    Vertex operator-(Vertex op2);
    Vertex operator+(Vertex op2);
    Vertex operator*(float op2);
    bool operator==(Vertex op2);
    void print();
    vector<float> getXYZ();
    float getX();
    float getY();
    float getZ();
    arma::Row<float> row();
    arma::Col<float> h(float w);
};

#endif