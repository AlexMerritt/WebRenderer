#ifndef __RENDERER__
#define __RENDERER__

#include "GraphicsDevice.h"
#include "../Graphics/Scene.h"
#include "../Graphics/Mesh.h"

#include "../ServiceProvider.h"

#include <vector>


class Renderer : public MainSystem
{
public:
    Renderer();
    virtual void Initialize();

	// RenderObject* CreateRenderObject(char* vertexShaderText, char* fragmentShaderText);
    RenderObject* CreateRenderObject(Mesh* pMesh, char* vertexShaderText, char* fragmentShaderText);

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