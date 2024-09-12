#ifndef PLY_H
#define PLY_H

#pragma once

#include "Object.h"

class Ply :  public Object
{
private:
    void load();

public:
    Ply(string fname, float r, float g, float b);
};
#endif