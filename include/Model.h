#ifndef MODEL_H
#define MODEL_H

#pragma once

#include "Obj.h"
#include "Ply.h"

template<class T>
class Model : public T
{
public:
    Model(string name, float r, float g, float b) : T(name,r,g,b) {}
    Model() : T("",0.0,0.0,0.0) {}

};

#endif