#include "Scene.h"

Scene::Scene(const std::string& strSceneName, int iWindowWidth, int iWindowHeight)
{
    m_strSceneName = strSceneName;

    float fFov = 90.0f;
    float fAspectRatio = (float)iWindowWidth / (float)iWindowHeight;

    m_pCamera = new Camera(); 
    m_pCamera->SetProjection(fFov, fAspectRatio, 0.1f, 1000.0f);
}

void Scene::Update()
{
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