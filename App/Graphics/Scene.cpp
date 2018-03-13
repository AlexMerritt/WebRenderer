#include "Scene.h"
#include "Mesh.h"
#include "../Util/Input.h"
#include "ShaderPrograms.h"
#include "../ServiceProvider.h"
#include "../Renderer/Renderer.h"

Scene::Scene(const std::string& strSceneName, int iWindowWidth, int iWindowHeight)
{
    m_strSceneName = strSceneName;

    float fFov = 90.0f;
    float fAspectRatio = (float)iWindowWidth / (float)iWindowHeight;

    m_pCamera = new Camera(); 
    m_pCamera->SetProjection(fFov, fAspectRatio, 0.1f, 1000.0f);

    // Create the meshs
    std::vector<Vertex> verticies;

    verticies.push_back(Vertex(-1.0, 2.0, 0.0));
    verticies.push_back(Vertex(0.0, -1.0, 0.0));
    verticies.push_back(Vertex(2.0, 0.0, 0.0));

    std::vector<unsigned int> indicies;
    indicies.push_back(0);
    indicies.push_back(1);
    indicies.push_back(2);

    Mesh mesh = Mesh(verticies, indicies);

    Renderer* pRenderer = Systems::Get<Renderer>();

    RenderObject* pRO = pRenderer->CreateRenderObject(&mesh, vs, fShaderStr);
    AddRenderObject(pRO);
}

void Scene::Update(double dDelta)
{

    if(Keyboard::Get()->IsKeyDown(65))
    {
        m_pCamera->Move(Vector3(0.1f, 0.0f, 0.0f));
    }
    else if(Keyboard::Get()->IsKeyDown(68))
    {
        m_pCamera->Move(Vector3(-0.1f, 0.0f, 0.0f));
    }


    m_pCamera->Update();
}

void Scene::Resize(int iWindowWidth, int iWindowHeight)
{
    UpdateCameras(iWindowWidth, iWindowHeight);
}

void Scene::UpdateCameras(int iWindowWidth, int iWindowHeight)
{
    float fFov = 90.0f;
    float fAspectRatio = (float)iWindowWidth / (float)iWindowHeight;

    m_pCamera = new Camera(); 
    m_pCamera->SetProjection(fFov, fAspectRatio, 0.1f, 1000.0f);
}