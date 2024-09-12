#ifndef DUCK_H
#define DUCK_H

#pragma once

#include "Model.h"

class Duck
{
public:
    Duck();
    void fly();                     //Dinamica de saltar (seria en shooted en el de Cannon)
    void draw(GLuint programID);
    bool hasPipeCollided(BoundariesBox counterBox);
    bool hasWatermelonCollided(BoundariesBox watermelonBox);

private:
    Vertex currentVertex;
    Vertex size;

    float force;
    float angle;
    vector<Vertex> duck_path;
    int duck_index;
    bool bounced;

    Model<Ply> duck;
    BoundariesBox collitionBox;
    bool collided;
    Model<Ply> roasted;

    glm::mat4 duck_transform;
};

#endif