#ifndef WATERMELON_H
#define WATERMELON_H

#pragma once

#include <vector>
#include <random>

#include "Model.h"
#include "Animation.h"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale


class Watermelon
{
public:
    Watermelon(GLuint programID);
    void draw();
    void move();
    BoundariesBox getBox();
    void show();
    void hide();

private:
    GLuint programID;
    //Model<Ply> watermelon;
    Model<Obj> watermelon;
    Vertex location;
    vector<Vertex> locations;
    glm::mat4 watermelon_transform;

    BoundariesBox collitionBox;
    bool collided;

    bool isVisible;

    float speed;
    vector<Vertex> watermelon_path;
    int watermelon_index;

    void setRandomLocation();
};

#endif