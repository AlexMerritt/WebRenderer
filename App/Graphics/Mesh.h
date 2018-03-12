#ifndef __MESH__
#define __MESH__

#include <vector>

#include "Vertex.h"

class Mesh
{
public:
    Mesh(std::vector<Vertex> verticies, std::vector<unsigned int> indicies)
    {
        m_verticies = verticies;
        m_indicies = indicies;
    }

    std::vector<Vertex>& GetVerticies() { return m_verticies; }
    std::vector<unsigned int>& GetIndicies() { return m_indicies; }

protected:
    std::vector<Vertex> m_verticies;
    std::vector<unsigned int> m_indicies;
};

#endif