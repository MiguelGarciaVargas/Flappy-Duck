#include "../include/Animation.h"
#include <math.h>
#include <cmath>

Animation::Animation()
{

}

vector<Vertex> Animation::line(Vertex v1, Vertex v2, float dt){
    vector<Vertex> v = {};
    
    for (float t=0.0; t <= 1.0+dt; t+=dt){
        v.push_back(v1 + (v2-v1) * t ); 
    }

    return v;
}

vector<Vertex> Animation::hermite(Vertex p1, Vertex p4, Vertex r1, Vertex r4, float dt){
    arma::Mat<float> MH =  {{2,-2,1,1}, 
                            {-3,3,-3,-1}, 
                            {0,0,1,0}, 
                            {1,0,0,0}};

    arma::Mat<float> GH = {};
    GH.insert_rows(0,p1.row());
    GH.insert_rows(1,p4.row());
    GH.insert_rows(2,r1.row());
    GH.insert_rows(3,r4.row());

    vector<Vertex> v = {};
    for (float t = 0.0; t < 1.0 + dt; t+=dt)
    {
        arma::Row<float> T = {powf(t,3), powf(t,2), t, 1};
        arma::Mat<float> Qt = T * MH * GH;

        Vertex tv(Qt(0,0), Qt(0,1), Qt(0,2));
        v.push_back(tv);
    }   
    return v; 
}

vector<Vertex> Animation::bezier(Vertex p1, Vertex p2, Vertex p3, Vertex p4, float dt){
    arma::Mat<float> MH={{-1,3,-3,1},{3,-6,3,0},{-3,3,0,0},{1,0,0,0}};
    arma::Mat<float> GH{};
    GH.insert_rows(0,p1.row());
    GH.insert_rows(1,p2.row());
    GH.insert_rows(2,p3.row());
    GH.insert_rows(3,p4.row());

    vector<Vertex> v={};
    for(float t=0.0;t<=11.0+dt;t+=dt){
        arma::Row<float> T ={powf(t,3),powf(t,2),t,1};
        arma::Mat<float> Qt = T * MH * GH;
        Vertex tv(Qt(0,0),Qt(0,1),Qt(0,2));
        v.push_back(tv);
    }
    return v;
}

glm::mat4 Animation::T(float d1, float d2, float d3){
    glm::mat4 t = glm::translate(glm::mat4(1.0f),glm::vec3(d1,d2,d3));
    
    return t;
}


glm::mat4 Animation::S(float s1, float s2, float s3){
    glm::mat4 s =  glm::scale(glm::mat4(1.0f), glm::vec3(s1,s2,s3));
    
    return s;
}
/*
BoundariesBox Animation::Sbox(float s, BoundariesBox box){
    BoundariesBox tempBox = BoundariesBox();
    tempBox.update(box.getMin().x * s, box.getMin().y * s, box.getMin().z * s);
   
    return tempBox;
}
*/

glm::mat4 Animation::Rx(float angle){
    glm::mat4 Rx = glm::rotate(glm::mat4(1.0f),glm::radians(angle),glm::vec3(1.0,0.0,0.0));
    return Rx;
}

glm::mat4 Animation::Ry(float angle){
    glm::mat4 Ry = glm::rotate(glm::mat4(1.0f),glm::radians(angle),glm::vec3(0.0,1.0,0.0));
    return Ry;
}

glm::mat4 Animation::Rz(float angle){
    glm::mat4 Rz = glm::rotate(glm::mat4(1.0f),glm::radians(angle),glm::vec3(0.0,0.0,1.0));
    return Rz;
}

float Animation::AngleToRadian(float angle){
    float radianes = angle * (M_PI / 180);
    return radianes;
}