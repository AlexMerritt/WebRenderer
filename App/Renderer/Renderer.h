#ifndef __RENDERER__
#define __RENDERER__

#include "GraphicsDevice.h"

class Renderer
{
public:
    Renderer();
    void Initialize();

    void DrawScene();

private:
    GraphicsDevice* m_pDevice;

    ShaderProgram* m_pProgram;
    Buffer* m_pVertexBuffer;
    Buffer* m_pIndexBuffer;
};

#endif