#include <iostream>
#include <vector>
#include "../include/Vertex.h"

using namespace std;

Vertex::Vertex()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vertex::Vertex(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vertex::print()
{
    cout << "(x: " << this->x << ", y:" << this->y << ", z:" << this->z << " )" << endl;
}

vector<float> Vertex::getXYZ()
{
    vector<float> lista = {this->x, this->y, this->z};

    return lista;
}

float Vertex::getX(){
    return this->x;
}
float Vertex::getY(){
    return this->y;
}
float Vertex::getZ(){
    return this->z;
}

Vertex Vertex::operator-(Vertex op2)
{
    return Vertex(this->x-op2.x, this->y-op2.y, this->z-op2.z);
}

Vertex Vertex::operator+(Vertex op2){
    return Vertex(this->x+op2.x, this->y+op2.y, this->z+op2.z);
}

Vertex Vertex::operator*(float op2){
    return Vertex(this->x*op2, this->y*op2, this->z*op2);
}

bool Vertex::operator==(Vertex op2){
    bool flag = false;
    vector<float> op2List = op2.getXYZ();
    if (this->x == op2List[0] && this->y == op2List[1] && this->z == op2List[2])
    {
        flag = true;
    }
    return flag;
}


arma::Row<float> Vertex::row(){
    arma::Row<float> r = {this->x, this->y, this->z};
    return r;
}

arma::Col<float> Vertex::h(float w){
    arma::Col<float> h = {this->x/w, this->y/w, this->z/w, w};
    return h;
}
