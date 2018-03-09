#ifndef __RENDER_OBJECT__
#define __RENDER_OBJECT__

#include "Buffer.h"
#include "Shader.h"

struct VertexType
{
    float x, y, z;
    // Changed to 4 at some point
    // float x, y, z, w;
};

class RenderObject
{
public:
    RenderObject(Shader* pShader, VertexBuffer* pVB, Buffer* pIB, unsigned int iNumElements) {
        m_pShader = pShader;
        m_pVertexBuffer = pVB;
        m_pIndexBuffer = pIB;
        m_iNumElements = iNumElements;
    }

    Shader* GetShader() { return m_pShader; }
    VertexBuffer* GetVertexBuffer() { return m_pVertexBuffer; }
    Buffer* GetIndexBuffer() { return m_pIndexBuffer; }
    unsigned int GetElementCount() { return m_iNumElements; }

private:
    Shader * m_pShader;
    VertexBuffer* m_pVertexBuffer;
    Buffer* m_pIndexBuffer;
    unsigned int m_iNumElements;
};

#endif