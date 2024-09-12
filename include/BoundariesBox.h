#ifndef BOUNDARIESBOX_H
#define BOUNDARIESBOX_H

#pragma once

#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <limits>

class BoundariesBox
{
public:
    BoundariesBox();
    void update(glm::vec3 point);  // Actualiza la caja delimitadora con un nuevo punto
    void reset();  // Reinicia la caja delimitadora

    void translateBox(float x, float y, float z);
    
    glm::vec3 getMin();
    glm::vec3 getMax();
    float getHeight();
    float getWidth();

    bool isColliding(BoundariesBox counterBox);


private:
    float width;
    float height;
    float depth; //Este probablemente no se utilice porque
                 //todo estara dentro de la misma z gg

    glm::vec3 minBounds;
    glm::vec3 maxBounds;
};

#endif