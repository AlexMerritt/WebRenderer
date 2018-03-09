#ifndef __RENDERER__
#define __RENDERER__

#include "GraphicsDevice.h"
#include "../Graphics/Scene.h"

#include <vector>


class Renderer
{
public:
    Renderer();
    void Initialize();

	RenderObject* CreateRenderObject();

    void SetScene(Scene* pScene) { m_pScene = pScene; }

	void Resize(int iWidth, int iHeight);

    void Render();

private:
    void DrawScene(Scene* pScene);

private:
    GraphicsDevice* m_pDevice;
    Scene* m_pScene;
};

#endif