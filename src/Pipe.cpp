#include "../include/Pipe.h"

Pipe::Pipe(bool type, float initialX)
{
    Animation an;
    this->isUpModel = type;

    //this->speed = .00023; //Modo facil
    this->speed = .00024;  //Modo normal --------------->>>>
    //this->speed = .00025; //Modo dificil
    this->definirModelos();
    this->initialX = initialX;
}

void Pipe::definirModelos()
{
    // smallUp = 0, mediupUp = 1, longUp = 2, longlongUp = 3
    // smallDown = 0, mediupUp = 1, longUp = 2, longlongUp = 3

    //for (int i = 0; i < 4 && isUpModel; ++i)  //<---------Descomentar y comentar abajo para modo hardcore (En move() tambien)
    for (int i = 0; i < 3 && isUpModel; ++i)
    {
        stringstream ss;
        ss << "models/pipe" << i << ".ply";
        string nombreArchivo = ss.str();
        Model<Ply> nuevoModelo;
        nuevoModelo = Model<Ply>(nombreArchivo, 1.0, 0.0, 1.0);
        this->listaModelos.push_back(nuevoModelo);
    }
    for (int i = 4; i < 8 && !isUpModel; ++i)
    {
        stringstream ss;
        ss << "models/pipe" << i << ".ply";
        string nombreArchivo = ss.str();
        Model<Ply> nuevoModelo;
        nuevoModelo = Model<Ply>(nombreArchivo, 1.0, 0.0, 1.0);
        this->listaModelos.push_back(nuevoModelo);
    }
}

void Pipe::draw(GLuint programID)
{
    Animation an;
    if (!this->pipe_path.empty())
    {
        float x = pipe_path[this->pipe_index].getX();
        float y = pipe_path[this->pipe_index].getY();
        float z = pipe_path[this->pipe_index].getZ();

        if (this->pipe_index < pipe_path.size() - 1)
        {
            this->pipe_index = this->pipe_index + 1;
            this->pipe_transform = an.T(x, y, x);
            this->collitionBox.translateBox(x, y, z);
        }
        else
        {
            this->move();
        }
    }
    pipe.draw(programID, this->pipe_transform);
}

void Pipe::move()
{
    Animation an;

    if (isUpModel)
    {
        random_device rd;
        mt19937 gen(rd());
        //uniform_int_distribution<int> distribucion(0, 3);  //<---------Descomentar y comentar abajo para modo hardcore (En definirModelos() tambien)
        uniform_int_distribution<int> distribucion(0, 2);
        this->pipe = listaModelos[distribucion(gen)];
        this->location = Vertex(initialX, -1.0, 0);
    }
    else
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> distribucion(0, 3);
        this->pipe = listaModelos[distribucion(gen)];
        this->location = Vertex(initialX, 1.0 - pipe.getBox().getWidth(), 0.0);
    }

    this->collitionBox = this->pipe.getBox();
    this->pipe_transform = an.T(this->location.getX(), this->location.getY(), this->location.getZ());
    this->collitionBox.translateBox(this->location.getX(), this->location.getY(), this->location.getZ());

    Vertex p1 = this->location;
    Vertex p2;
    if (isUpModel)
    {
        p2 = Vertex(p1.getX()-5.0, p1.getY(), p1.getZ());
    }
    else
    {
        p2 = Vertex(p1.getX()-5.0, p1.getY(), p1.getZ());
    }

    this->pipe_path = an.line(p1, p2, speed);
    this->pipe_index = 0;
}

BoundariesBox Pipe::getBox()
{
    return this->collitionBox;
}
