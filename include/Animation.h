#ifndef ANIMATION_H
#define ANIMATION_H

#pragma once

#include <iostream>
#include <vector>
#include <armadillo>
#include "Vertex.h"
#include "Model.h"

#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale

using namespace std;

class Animation
{
public:
    Animation();
    vector<Vertex> line(Vertex v1, Vertex v2, float dt);
    vector<Vertex> hermite(Vertex p1, Vertex p4, Vertex r1, Vertex r4, float dt);
    vector<Vertex> bezier(Vertex p1, Vertex p2, Vertex p3, Vertex p4, float dt);

    glm::mat4 T(float d1, float d2, float d3);
    glm::mat4 S(float s1, float s2, float s3);
    glm::mat4 Sbox(float s1, float s2, float s3);
    glm::mat4 Rx(float angle);
    glm::mat4 Ry(float angle);
    glm::mat4 Rz(float angle);
private:
    float AngleToRadian(float angle);
};


#endif