#ifndef PIPE_H
#define PIPE_H

#pragma once

#include "Model.h"
#include "Animation.h"
#include <sstream>
#include <random>

class Pipe
{
public:
    Pipe(bool type, float initialX);
    void draw(GLuint programID);
    void move();
    BoundariesBox getBox();

private:
    vector<Model<Ply>> listaModelos;
    bool isUpModel;
    void definirModelos();
    float initialX;
    float speed;

    Model<Ply> pipe;
    Vertex location;
    glm::mat4 pipe_transform;
    vector<Vertex> pipe_path;
    int pipe_index;

    BoundariesBox collitionBox;

};

#endif