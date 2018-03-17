#ifndef __RENDER_OBJECT__
#define __RENDER_OBJECT__

#include "Buffer.h"
#include "../Renderer/Shader.h"
#include "Material.h"

class RenderObject
{
public:
    RenderObject(Material* pMaterial, VertexBuffer* pVB, Buffer* pIB, unsigned int iNumElements) {
        m_pMaterial = pMaterial;
        m_pVertexBuffer = pVB;
        m_pIndexBuffer = pIB;
        m_iNumElements = iNumElements;
    }

    Material* GetMaterial() { return m_pMaterial; }
    VertexBuffer* GetVertexBuffer() { return m_pVertexBuffer; }
    Buffer* GetIndexBuffer() { return m_pIndexBuffer; }
    unsigned int GetElementCount() { return m_iNumElements; }

private:
    Material* m_pMaterial;
    VertexBuffer* m_pVertexBuffer;
    Buffer* m_pIndexBuffer;
    unsigned int m_iNumElements;
};

#endif