#include "../include/Watermelon.h"
Watermelon::Watermelon(GLuint programID)
{
    this->programID = programID;

    Animation an;
    //this->watermelon = Model<Ply>("models/watermelon.ply", 0.0, 1.0, 0.0);
    this->watermelon = Model<Obj>("models/watermelon.obj", 0.0, 1.0, 0.0);

    this->locations.push_back(Vertex(1.0, 0.5, 0.0));
    this->locations.push_back(Vertex(1.0, 0.25, 0.0));
    this->locations.push_back(Vertex(1.0, 0.0, 0.0));
    this->locations.push_back(Vertex(1.0, -0.25, 0.0));
    this->locations.push_back(Vertex(1.0, -0.5, 0.0));

    this->speed = .0003;

    this->isVisible = true;
    this->collided = false;
    this->collitionBox = this->watermelon.getBox();
    this->collitionBox.translateBox(this->location.getX(), this->location.getY(), this->location.getZ());

    location = locations[2];
}

void Watermelon::draw()
{
    if (isVisible)
    {
        Animation an;
        if (!this->watermelon_path.empty())
        {
            float x = watermelon_path[this->watermelon_index].getX();
            float y = watermelon_path[this->watermelon_index].getY();
            float z = watermelon_path[this->watermelon_index].getZ();

            if (this->watermelon_index < watermelon_path.size() - 1)
            {
                this->watermelon_index = this->watermelon_index + 1;
                this->watermelon_transform = an.T(x, y, x);
                this->collitionBox.translateBox(x, y, z);
            }
            else
            {
                this->move();
            }
        }
        watermelon.draw(this->programID, this->watermelon_transform);
    }
}

void Watermelon::move()
{
    setRandomLocation();
    Animation an;
    this->watermelon_transform = an.T(this->location.getX(), this->location.getY(), this->location.getZ());
    this->collitionBox.translateBox(this->location.getX(), this->location.getY(), this->location.getZ());
    watermelon.draw(this->programID, this->watermelon_transform);

    Vertex p1 = this->location;
    Vertex p2 = Vertex(-1.0, p1.getY(), p1.getZ());

    this->watermelon_path = an.line(p1, p2, speed);
    this->watermelon_index = 0;
}

void Watermelon::setRandomLocation()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, locations.size() - 1);

    int randomIndex = dist(gen);
    this->location = this->locations[randomIndex];
}

BoundariesBox Watermelon::getBox()
{
    return this->collitionBox;
}

void Watermelon::hide()
{
    if (isVisible)
    {
        this->move();
        isVisible = false;
    }
}

void Watermelon::show()
{
    isVisible = true;
}