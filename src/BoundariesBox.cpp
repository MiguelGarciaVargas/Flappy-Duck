#include "../include/BoundariesBox.h"

// Probablemente buena idea pero demasiado complicada.
// Mejor anadir una caja predefinida

BoundariesBox::BoundariesBox()
{
    reset();
}

void BoundariesBox::update(glm::vec3 point)
{
    minBounds.x = fmin(minBounds.x, point.x);
    minBounds.y = fmin(minBounds.y, point.y);
    minBounds.z = fmin(minBounds.z, point.z);

    maxBounds.x = fmax(maxBounds.x, point.x);
    maxBounds.y = fmax(maxBounds.y, point.y);
    maxBounds.z = fmax(maxBounds.z, point.z);

    height = maxBounds.x - minBounds.x;
    width = maxBounds.y - minBounds.y;
    depth = maxBounds.z - minBounds.z;
}


void BoundariesBox::translateBox(float x, float y, float z)
{
    /*
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x,y,z));
    minBounds = glm::vec3(translationMatrix * glm::vec4(minBounds, 1.0f));
    maxBounds = glm::vec3(translationMatrix * glm::vec4(maxBounds, 1.0f));
    */
    // Calcular el vector de traslación
    glm::vec3 translateVector = glm::vec3(x, y, z) - minBounds;

    // Aplicar la traslación a los límites mínimo y máximo
    minBounds += translateVector;
    maxBounds += translateVector;

    height = maxBounds.x - minBounds.x;
    width = maxBounds.y - minBounds.y;
    depth = maxBounds.z - minBounds.z;
}

bool BoundariesBox::isColliding(BoundariesBox counterBox){
    // Verifica la colisión en el eje x
    bool collisionX = (maxBounds.x >= counterBox.minBounds.x) && (minBounds.x <= counterBox.maxBounds.x);

    // Verifica la colisión en el eje y
    bool collisionY = (maxBounds.y >= counterBox.minBounds.y) && (minBounds.y <= counterBox.maxBounds.y);

    // Verifica la colisión en el eje z
    bool collisionZ = (maxBounds.z >= counterBox.minBounds.z) && (minBounds.z <= counterBox.maxBounds.z);

    return collisionX && collisionY && collisionZ;

}

void BoundariesBox::reset()
{
    minBounds = glm::vec3(std::numeric_limits<float>::max());
    maxBounds = glm::vec3(std::numeric_limits<float>::lowest());

    width = 0;
    height = 0;
    depth = 0;
}

glm::vec3 BoundariesBox::getMin()
{
    return minBounds;
}

glm::vec3 BoundariesBox::getMax()
{
    return maxBounds;
}

float BoundariesBox::getHeight(){
    return height;
}

float BoundariesBox::getWidth(){
    return width;
}