#include "Scene.h"
#include "../Util/Input.h"

Scene::Scene(const std::string& strSceneName, int iWindowWidth, int iWindowHeight)
{
    m_strSceneName = strSceneName;

    float fFov = 90.0f;
    float fAspectRatio = (float)iWindowWidth / (float)iWindowHeight;

    m_pCamera = new Camera(); 
    m_pCamera->SetProjection(fFov, fAspectRatio, 0.1f, 1000.0f);
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