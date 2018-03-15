#ifndef __VERTEX__
#define __VERTEX__

#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#include "Attribute.h"

struct Vertex
{
    Vertex(float x, float y, float z)
    {
        Position = Vector3(x, y, z);
    }

    Vertex(Vector3 position)
    {
        Position = position;
    }

    static std::vector<VertexAttribute> GetAttributes()
    {
        std::vector<VertexAttribute> attributes;

        attributes.push_back(VertexAttribute(sizeof(Vector3)));

        return attributes;
    }

    Vector3 Position;
};

#endif