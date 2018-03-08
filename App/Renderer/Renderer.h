#ifndef __RENDERER__
#define __RENDERER__

#include "GraphicsDevice.h"
#include <vector>

class Renderer
{
public:
    Renderer();
    void Initialize();

	RenderObject* CreateRenderObject();

    void DrawScene();

	void Resize(int iWidth, int iHeight);

private:
    GraphicsDevice * m_pDevice;

	std::vector<RenderObject*> m_objects;

    RenderObject* m_pObj;

    Shader* m_pProgram;
    VertexBuffer* m_pVertexBuffer;
    Buffer* m_pIndexBuffer;
};

#endif