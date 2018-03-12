#ifndef __VERTEX__
#define __VERTEX__

#include "../Math/Vector3.h"

struct Vertex
{
    Vertex(float x, float y, float z)
    {
        Position = Vector3(x, y, z);
    }
    Vector3 Position;
};

#endif