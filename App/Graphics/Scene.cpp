#include "Scene.h"
#include "Mesh.h"
#include "../Util/Input.h"
#include "ShaderPrograms.h"
#include "../ServiceProvider.h"
#include "../Renderer/Renderer.h"

#include <stdlib.h>

Scene::Scene(const std::string& strSceneName, int iWindowWidth, int iWindowHeight)
{
    m_strSceneName = strSceneName;

    float fFov = 90.0f;
    float fAspectRatio = (float)iWindowWidth / (float)iWindowHeight;

    m_pCamera = new Camera(); 
    m_pCamera->SetProjection(fFov, fAspectRatio, 0.1f, 1000.0f);
    
    m_pCamera->SetPosition(Vector3(0, 0, -10));

    std::string strN = "test name";

    // Json test
    nlohmann::json j = {
        {"pi", 3.141},
        {"happy", true},
        {"name", strN},
        {"nothing", nullptr},
        {"answer", {
            {"everything", 42}
        }},
        {"list", {1, 0, 2}},
        {"object", {
            {"currency", "USD"},
            {"value", 42.99}
        }}
    };

    std::string name = j["name"];
    float piz = j["pi"];
    printf("%f\n", piz);
    printf("%s\n", name.c_str());

    CreateModel();
    // CreateTest();
}

void Scene::Update(double dDelta)
{

    if(Keyboard::Get()->IsKeyDown(KeyCode::D))
    {
        m_pCamera->Move(Vector3(0.1f, 0.0f, 0.0f));
    }
    
    if(Keyboard::Get()->IsKeyDown(KeyCode::A))
    {
        m_pCamera->Move(Vector3(-0.1f, 0.0f, 0.0f));
    }

    if(Keyboard::Get()->IsKeyDown(KeyCode::W))
    {
        m_pCamera->Move(Vector3(0, 0.0f, 0.1f));
    }

    if(Keyboard::Get()->IsKeyDown(KeyCode::S))
    {
        m_pCamera->Move(Vector3(0, 0, -0.1f));
    }

    m_pCamera->Update();

    Randomize();
    
}

void Scene::Randomize()
{
    std::vector<Vertex>& verts = pMesh->GetVerticies();

    int iMaxUpates = verts.size() - 1;

    int iPointsToUpdate = rand() % iMaxUpates;

    

    for(int i = 0; i < iPointsToUpdate; ++i){
        int iPoint = rand() % (verts.size() - 1);
        
        float fScale = (float) rand()/RAND_MAX;
        fScale *= 0.1f;

        int iDir = ((rand() % 2) * 2) - 1;

        // printf("Num Verts:%d, Updating %d\n", verts.size(), iPointsToUpdate);
        // printf("%d\n", iPoint);
        Vertex& vertex = verts[iPoint];
        Vector3 position = vertex.Position;

        // int iLength = position.x + position.z;
        // int iXDir = (position.x / iLength) * iDir;
        // int iZDir = (position.z / iLength) * iDir;

        // position.x = (float)iXDir * fScale;
        // position.z = (float)iZDir * fScale;
        position.x += (float)iDir * fScale;

        vertex.Position = position;
    }

    Systems::Get<Renderer>()->Update(pObj, pMesh);
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

void Scene::CreateModel()
{
    const float fLevelHeight = 0.05f;

    int iNumLevels = 100;
    float fCurrentHeight = -((iNumLevels / 2) * fLevelHeight);

    int iNumFacesPerLevel = 360;

    float fWidth = 3.0f;

    float fPercentAngle = (360.0f / (float)iNumFacesPerLevel) * 0.0174533f;

    std::vector<Vertex> verticies;

    for(int j = 0; j < iNumLevels + 1; ++j)
    {
        for(int i = 0; i < iNumFacesPerLevel; ++i)
        {
            float fAngle = fPercentAngle * (float)i;
            float fX = sin(fAngle) * fWidth;
            float fZ = cos(fAngle) * fWidth;

            Vector3 position(fX, fCurrentHeight, fZ);
            Vector3 color(0.5f, 0.7f, 0.5f);

            verticies.push_back(Vertex(position, color));        

        }
        fCurrentHeight += fLevelHeight;
    }

    const int iNumVertexOffset = 2;

    std::vector<unsigned int> indicies;

    for(int j = 0; j < iNumLevels; ++j)
    {
        int iCurrentLevelIndex = j * iNumFacesPerLevel;

        for(int i = 0; i < iNumFacesPerLevel; ++i)
        {
            int iCurr = iCurrentLevelIndex + i;
            int iCurrentLevelNextIndex;

            int iNextLevelIndex = iCurrentLevelIndex + i + iNumFacesPerLevel;
            int iNextLevelNextIndex;

            if((i + 1) >= iNumFacesPerLevel)
            {
                iCurrentLevelNextIndex = iCurrentLevelIndex;
                iNextLevelNextIndex = iCurrentLevelIndex + iNumFacesPerLevel;
            }
            else
            {
                iCurrentLevelNextIndex = iCurr + 1;
                iNextLevelNextIndex = iNextLevelIndex + 1;
            }

            indicies.push_back(iNextLevelIndex);
            indicies.push_back(iCurr);
            indicies.push_back(iCurrentLevelNextIndex);

            indicies.push_back(iNextLevelIndex);
            indicies.push_back(iCurrentLevelNextIndex);
            indicies.push_back(iNextLevelNextIndex);
        }
    }

    pMesh = new Mesh(verticies, Vertex::GetAttributes(), sizeof(Vertex), indicies);

    Renderer* pRenderer = Systems::Get<Renderer>();

    Material* pMat = pRenderer->CreateMaterial(COLOR_SHADER);
    pObj = pRenderer->CreateRenderObject(pMesh, pMat);
    AddRenderObject(pObj);
}

void Scene::CreateTest()
{
    std::vector<Vertex> verts;

    verts.push_back(Vertex(Vector3(0,1,0), Vector3(0.5f, 0, 0)));
    verts.push_back(Vertex(Vector3(-3,0,0), Vector3(0, 0, 0.5f)));
    verts.push_back(Vertex(Vector3(1,0,0), Vector3(0, 0.5f, 0)));

    std::vector<unsigned int> inds;
    inds.push_back(0);
    inds.push_back(1);
    inds.push_back(2);

    Renderer* pRenderer = Systems::Get<Renderer>();

    pMesh = new Mesh(verts, Vertex::GetAttributes(), sizeof(Vertex), inds);
    Material* pMat = pRenderer->CreateMaterial(COLOR_SHADER);

    pObj = pRenderer->CreateRenderObject(pMesh, pMat);

    AddRenderObject(pObj);
}
