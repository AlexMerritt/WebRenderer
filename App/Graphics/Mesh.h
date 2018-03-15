#ifndef __MESH__
#define __MESH__

#include <vector>

#include "Vertex.h"
#include "Attribute.h"

class Mesh
{
public:
    Mesh(std::vector<Vertex> verticies, std::vector<VertexAttribute> vertexAttributes, unsigned int iVertexElementSize, std::vector<unsigned int> indicies)
    {
        m_verticies = verticies;
        m_vertexAttributes = vertexAttributes;
        m_iVertexElementSize = iVertexElementSize;
        m_indicies = indicies;
    }

    std::vector<Vertex>& GetVerticies() { return m_verticies; }
    std::vector<VertexAttribute>& GetAttributes() { return m_vertexAttributes; }
    unsigned int GetVertexElementSize() { return m_iVertexElementSize; }

    std::vector<unsigned int>& GetIndicies() { return m_indicies; }

protected:
    std::vector<Vertex> m_verticies;
    std::vector<VertexAttribute> m_vertexAttributes;
    unsigned int m_iVertexElementSize;

    std::vector<unsigned int> m_indicies;
};

#endif