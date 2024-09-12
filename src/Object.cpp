#include "../include/Object.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <random>

Object::Object(string fname, float r, float g, float b)
{
    this->fname = fname;
    this->r = r;
    this->g = g;
    this->b = b;
}

vector<string> Object::split(const string &str, const string &delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;

    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos)
            pos = str.length();
        string token = str.substr(prev, pos - prev);
        if (!token.empty())
            tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());

    return tokens;
}

void Object::imprimir()
{
    int i = 1;
    for (Face f : ListaCaras)
    {
        cout << "Face: " << i++ << endl;
        f.print();
        cout << endl;
    }
}

void Object::load()
{
    cout << "Función load en Object" << endl;
}


BoundariesBox Object::getBox(){
    return this->box;
}

void Object::draw(GLuint programID, glm::mat4 transform)
{
    // Transformaciones
    this->transform = transform;

    GLuint MatrixID = glGetUniformLocation(programID, "Transform");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &transform[0][0]);

    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
    glVertexAttribPointer(
        0,        // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        (void *)0 // array buffer offset
    );
    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, this->colorbuffer);
    glVertexAttribPointer(
        1,        // attribute. No particular reason for 1, but must match the layout in the shader.
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        (void *)0 // array buffer offset
    );
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, this->datasize); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
}

void Object::setData()
{
    vector<GLfloat> vertex_buffer_data = {};
    vector<GLfloat> color_buffer_data = {};

    vector<float> rgb = this->getRGB();
    float temp;

    for (Face f : this->ListaCaras)
    {
        vector<Vertex> listaVertices;
        for (Edge e : f.getEdges())
        {
            Vertex vi = e.getVi();
            Vertex vf = e.getVf();
            bool viFlag = true;
            bool vfFlag = true;

            for (int i = 0; i < listaVertices.size(); i++)
            {
                if (listaVertices[i] == vi)
                {
                    viFlag = false;
                }
                if (listaVertices[i] == vf)
                {
                    vfFlag = false;
                }
            }
            if (viFlag)
            {
                listaVertices.push_back(vi);
                vector<float> viVector = vi.getXYZ();
                vertex_buffer_data.push_back(viVector[0]);
                color_buffer_data.push_back(rgb[0]);
                vertex_buffer_data.push_back(viVector[1]);
                color_buffer_data.push_back(rgb[1]);
                vertex_buffer_data.push_back(viVector[2]);
                color_buffer_data.push_back(rgb[2]);
            }
            if (vfFlag)
            {
                listaVertices.push_back(vf);
                vector<float> vfVector = vf.getXYZ();
                vertex_buffer_data.push_back(vfVector[0]);
                color_buffer_data.push_back(rgb[0]);
                vertex_buffer_data.push_back(vfVector[1]);
                color_buffer_data.push_back(rgb[1]);
                vertex_buffer_data.push_back(vfVector[2]);
                color_buffer_data.push_back(rgb[2]);
            }
        }
        // rgb = this->colorSwap(rgb);
    }

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    glGenBuffers(1, &this->vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(GLfloat), &vertex_buffer_data[0], GL_STATIC_DRAW);
    this->datasize = vertex_buffer_data.size();

    glGenBuffers(1, &this->colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, color_buffer_data.size() * sizeof(GLfloat), &color_buffer_data[0], GL_STATIC_DRAW);
}

vector<float> Object::colorSwap(vector<float> rgb)
{
    // V1 se intercambian los valores entre ellos
    /*
    float temp;
    temp = rgb[0];
    for (int i = 0; i < 2; i++){
        rgb[i] = rgb[i+1];
    }
    rgb[2] = temp;
    */

    // V2 incremento y decremento recomendado empezar de 0 0 0
    /*
    float suma = .1;
    for (int i = 0; i < 3; i++)
    {
        if (rgb[i] == 1 || rgb[i] == 0)
        {
            suma*=-1;
        }
        rgb[i] += suma;

    }
    return rgb;
    */

    // V3 usando numeros aleatorios

    for (int i = 0; i < 3; i++)
    {
        // Crear un generador de números aleatorios
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(0.0, 1.0);

        // Generar un número aleatorio entre 0.0 y 1.0
        float numero_aleatorio = dis(gen);
        // float numero_aleatorio = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        rgb[i] = numero_aleatorio;
    }
    return rgb;
}

vector<float> Object::getRGB()
{
    vector<float> rgbVector = {this->r, this->g, this->b};
    return rgbVector;
}