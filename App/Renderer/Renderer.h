#ifndef __RENDERER__
#define __RENDERER__

#include "GraphicsDevice.h"
#include "../Graphics/Scene.h"
#include "../Graphics/Mesh.h"
#include "../Graphics/Material.h"

#include "../ServiceProvider.h"

#include <vector>
#include <map>


class Renderer : public MainSystem
{
public:
    Renderer();
    virtual void Initialize();

	// RenderObject* CreateRenderObject(char* vertexShaderText, char* fragmentShaderText);
    RenderObject* CreateRenderObject(Mesh* pMesh, const std::string& vertexShaderText, const std::string& fragmentShaderText);
    RenderObject* CreateRenderObject(Mesh* pMesh, Material* pMaterial);
    Material* CreateMaterial(std::string strShaderName);

    void Update(RenderObject* pRO, Mesh* pMesh);

    void SetScene(Scene* pScene) { m_pScene = pScene; }

	void Resize(int iWidth, int iHeight);

    void Render();

private:
    void DrawScene(Scene* pScene);

private:
    GraphicsDevice* m_pDevice;
    Scene* m_pScene;

    std::map<std::string, Shader*> m_loadedShaders;
};

#endif