#ifndef OBJECT_H
#define OBJECT_H

#pragma once

#include <iostream>
#include <fstream>
#include "Face.h"
#include "BoundariesBox.h"

#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
#include <vector>
#include <string>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale


using namespace std;

// Clase abstracta
class Object
{
public:
    Object(string fname, float r, float g, float b);
    void imprimir();
    BoundariesBox getBox();
    void draw(GLuint programID, glm::mat4 transform);

private:
    vector<float> colorSwap(vector<float> rgb);
    vector<float> getRGB();

protected:  
    string fname;
    vector<Vertex> ListaVertices;
    vector<Face> ListaCaras;

    vector<string> split(const string &str, const string &delim);
    BoundariesBox box;

    virtual void load() = 0;
    
    GLuint vertexbuffer;
	GLuint colorbuffer;
    //GLuint programID;
    GLuint datasize;

    glm::mat4 transform;

    float r;
    float g;
    float b;

    void setData();
};

#endif