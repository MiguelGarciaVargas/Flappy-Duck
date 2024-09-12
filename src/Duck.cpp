#include "../include/Duck.h"
#include "../include/Model.h"
#include "../include/Animation.h"

Duck::Duck()
{
    this->currentVertex = Vertex(-0.85, 0.0, 0.0);
    // this->size = Vertex(.009, .009, .009);

    this->duck = Model<Ply>("models/duck.ply", 1.0, 0.0, 0.0);
    this->roasted = Model<Ply>("models/roasted.ply", 1.0, 0.0, 0.0);
    // duck has the OG box, in case of
    this->collitionBox = this->duck.getBox();
    this->collided = false;

    this->force = 0.5;
    this->duck_index = 0;

    Animation an;

    this->duck_transform = an.T(this->currentVertex.getX(), this->currentVertex.getY(), this->currentVertex.getZ());
    this->collitionBox.translateBox(this->currentVertex.getX(), this->currentVertex.getY(), this->currentVertex.getZ());
}

void Duck::fly()
{
    Animation an;
    Vertex p1 = this->currentVertex;
    Vertex p2 = Vertex(p1.getX(), p1.getY() + .8, p1.getZ());
    Vertex p3 = Vertex(p2.getX(), p2.getY() - .7, p2.getZ());
    Vertex p4 = Vertex(p3.getX(), p3.getY() - 1, p3.getZ());

    this->duck_path = an.bezier(p1, p2, p3, p4, 0.001f);
    this->duck_index = 0;
}

void Duck::draw(GLuint programID)
{
    Animation an;
    if (!collided)
    {
        if (!this->duck_path.empty())
        {
            float x = duck_path[this->duck_index].getX();
            float y = duck_path[this->duck_index].getY();
            float z = duck_path[this->duck_index].getZ();

            if (this->duck_index < duck_path.size() - 1)
            {
                this->duck_index = this->duck_index + 1;
            }
            else
            {
                this->duck_index = 0;
            }
            this->duck_transform = an.T(x, y, z);
            this->currentVertex = Vertex(x, y, z);
            this->collitionBox.translateBox(x, y, z);
        }
        duck.draw(programID, this->duck_transform);
    }
    else
    {
        this->duck_transform =  this->duck_transform * an.Ry(.02);
        roasted.draw(programID, this->duck_transform);
    }
}

bool Duck::hasPipeCollided(BoundariesBox counterBox)
{
    if (!collided)
    {
        Animation an;
        this->duck_transform = an.T(-.25,-.25,0.0);
        collided = this->collitionBox.isColliding(counterBox);
    }
    
    return collided;
}

bool Duck::hasWatermelonCollided(BoundariesBox watermelonBox){
    return this->collitionBox.isColliding(watermelonBox);
}


