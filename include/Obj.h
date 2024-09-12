#ifndef OBJ_H
#define OBJ_H

#pragma once

#include "Object.h"

class Obj : public Object
{
private:
    void load();

public:
    Obj(string fname, float r, float g, float b);
};

#endif