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
        Color = Vector3(0, 0, 0);
    }

    Vertex(Vector3 position, Vector3 color)
    {
        Position = position;
        Color = color;
    }

    static std::vector<VertexAttribute> GetAttributes()
    {
        std::vector<VertexAttribute> attributes;

        attributes.push_back(VertexAttribute(sizeof(Vector3)));
        attributes.push_back(VertexAttribute(sizeof(Vector3)));

        return attributes;
    }

    Vector3 Position;
    Vector3 Color;
};

#endif