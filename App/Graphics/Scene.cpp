#include "Scene.h"
#include "Mesh.h"
#include "../Util/Input.h"
#include "ShaderPrograms.h"
#include "../ServiceProvider.h"
#include "../Renderer/Renderer.h"

#include <stdlib.h>

const int NUM_FACES_PER_LEVEL = 360;
int NUM_LEVELS = 100;
const float fLevelHeight = 0.05f;

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

    m_pMesh = CreateMesh();

    m_pObj = CreateModel(m_pMesh);
    m_pObj->GetTransform()->Move(Vector3(5.0f, 0.0f, 0.0f));

    m_pObj2 = CreateModel(m_pMesh);
    m_pObj2->GetTransform()->Move(Vector3(-5.0f, 0.0f, 0.0f));
    m_pObj2->GetTransform()->SetScale(Vector3(0.5f, 0.5f, 0.5f));
    // CreateTest();
}

void Scene::Update(double dDelta)
{
    float fSpeed = 10.0f * (dDelta);

    if(Keyboard::Get()->IsKeyDown(KeyCode::D))
    {
        m_pCamera->Move(Vector3(fSpeed, 0.0f, 0.0f));
    }
    
    if(Keyboard::Get()->IsKeyDown(KeyCode::A))
    {
        m_pCamera->Move(Vector3(-fSpeed, 0.0f, 0.0f));
    }

    if(Keyboard::Get()->IsKeyDown(KeyCode::W))
    {
        m_pCamera->Move(Vector3(0, 0.0f, fSpeed));
    }

    if(Keyboard::Get()->IsKeyDown(KeyCode::S))
    {
        m_pCamera->Move(Vector3(0, 0, -fSpeed));
    }

    m_pCamera->Update();

    // int iRandValue = rand() % 3;

    // float fVal = m_pOffsetColorParam->Value[iRandValue];

    // fVal += 0.025f;
    // if(fVal > 1.0f)
    // {
    //     fVal = 0.0f;
    // }

    // m_pOffsetColorParam->Value[iRandValue] = fVal;

    static float colorAngle = 0.0f;

    m_pOffsetColorParam->Value[0] = sin(colorAngle);
    m_pOffsetColorParam->Value[1] = cos(colorAngle / 3.0f);
    m_pOffsetColorParam->Value[2] = tan(colorAngle / 6.3f);

    colorAngle +=  dDelta;

    
    float fRotationSpeed = 1.7f / 2.0f * dDelta;

    Randomize(m_pMesh);

    Systems::Get<Renderer>()->Update(m_pObj, m_pMesh);

    Vector3 rotation = Vector3(fRotationSpeed / 2.0f, fRotationSpeed / 3.0f, fRotationSpeed);
    m_pObj->GetTransform()->Rotate(rotation);

    Systems::Get<Renderer>()->Update(m_pObj2, m_pMesh);
    Vector3 rotation2 = Vector3(fRotationSpeed / 5.0f, fRotationSpeed, fRotationSpeed * 1.5f);
    m_pObj2->GetTransform()->Rotate(rotation2);
}

void Scene::Randomize(Mesh* pMesh)
{
    std::vector<Vertex>& verts = pMesh->GetVerticies();

    int iMaxUpates = verts.size()  - 1;

    int iPointsToUpdate = rand() % iMaxUpates;    

    for(int i = 0; i < iPointsToUpdate; ++i)
    {
        int iPoint = rand() % (verts.size() - 1);
        
        float fScale = (float) rand()/RAND_MAX;
        fScale *= 0.015f;

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

    for(int i = 0; i < NUM_LEVELS; ++i)
    {
        int levelStartIndex = i * NUM_FACES_PER_LEVEL;
        int levelEndIndex = ((i + 1) * NUM_FACES_PER_LEVEL) - 1;
        int previousLevel = i - 1;
        if(previousLevel < 0) {
            previousLevel = 1;
        }

        previousLevel *= NUM_FACES_PER_LEVEL;

        // printf("%d, %d, %d\n", previousLevel, levelStartIndex, levelEndIndex);
        
        for(int j = 0; j < NUM_FACES_PER_LEVEL; ++j)
        {
            int iCurrentIndex = levelStartIndex + j;
            int iNext;
            int iPrev;

            iNext = iCurrentIndex + 1;
            if(iNext >= levelEndIndex)
            {
                iNext = levelStartIndex;
            }

            iPrev = previousLevel + j;

            // printf("%d, %d, %d\n", iPrev, iCurrentIndex, iNext);
            // iPrev = iCurrentIndex - 1;
            // if(iPrev < levelStartIndex)
            // {
            //     iPrev = levelEndIndex;
            // }

            Vertex& vert = verts[iCurrentIndex];

            Vertex& next = verts[iNext];
            Vertex& prev = verts[iPrev];

            // printf("(%f, %f, %f), (%f, %f, %f), (%f, %f, %f)\n", prev.Position.x, prev.Position.y, prev.Position.z, vert.Position.x, vert.Position.y, vert.Position.z, next.Position.x, next.Position.y, next.Position.z);

            Vector3 u = next.Position - vert.Position;
            Vector3 v = prev.Position - vert.Position;

            Vector3 normal = CrossP(u, v);
            normal.Normalize();

            // printf("%f, %f, %f\n", normal.x, normal.y, normal.z);

            // float nX, nY, nZ;

            // nX = (u.y * v.z) - (u.z * v.y);
            // nY = (u.z * v.x) - (u.x * v.z);
            // nZ = (u.x * v.y) - (u.y * v.x);

            vert.Normal = normal;
        }
    }
}

void Scene::Resize(int iWindowWidth, int iWindowHeight)
{
    UpdateCameras(iWindowWidth, iWindowHeight);
}

void Scene::UpdateCameras(int iWindowWidth, int iWindowHeight)
{
    float fFov = 90.0f;
    float fAspectRatio = (float)iWindowWidth / (float)iWindowHeight;

    m_pCamera->SetProjection(fFov, fAspectRatio, 0.1f, 1000.0f);
}

Mesh* Scene::CreateMesh()
{
    

    float fCurrentHeight = -((NUM_LEVELS / 2) * fLevelHeight);

    

    float fWidth = 3.0f;

    float fPercentAngle = (360.0f / (float)NUM_FACES_PER_LEVEL) * 0.0174533f;

    std::vector<Vertex> verticies;

    for(int j = 0; j < NUM_LEVELS + 1; ++j)
    {
        for(int i = 0; i < NUM_FACES_PER_LEVEL; ++i)
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

    for(int j = 0; j < NUM_LEVELS; ++j)
    {
        int iCurrentLevelIndex = j * NUM_FACES_PER_LEVEL;

        for(int i = 0; i < NUM_FACES_PER_LEVEL; ++i)
        {
            int iCurr = iCurrentLevelIndex + i;
            int iCurrentLevelNextIndex;

            int iNextLevelIndex = iCurrentLevelIndex + i + NUM_FACES_PER_LEVEL;
            int iNextLevelNextIndex;

            if((i + 1) >= NUM_FACES_PER_LEVEL)
            {
                iCurrentLevelNextIndex = iCurrentLevelIndex;
                iNextLevelNextIndex = iCurrentLevelIndex + NUM_FACES_PER_LEVEL;
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

    return new Mesh(verticies, Vertex::GetAttributes(), sizeof(Vertex), indicies);
}

RenderObject* Scene::CreateModel(Mesh* pMesh)
{
    Renderer* pRenderer = Systems::Get<Renderer>();

    Material* pMat = pRenderer->CreateMaterial(COLOR_SHADER);
    std::vector<float> colors;
    colors.push_back(0.5f);
    colors.push_back(-0.1f);
    colors.push_back(-0.2f);

    m_pOffsetColorParam = new FloatParameter();
    m_pOffsetColorParam->Name = "ColorOffset";
    m_pOffsetColorParam->Value = colors;

    pMat->SetFloatParam(m_pOffsetColorParam);

    RenderObject* pObj = pRenderer->CreateRenderObject(pMesh, pMat);
    AddRenderObject(pObj);

    return pObj;
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

    m_pMesh = new Mesh(verts, Vertex::GetAttributes(), sizeof(Vertex), inds);
    Material* pMat = pRenderer->CreateMaterial(COLOR_SHADER);

    m_pObj = pRenderer->CreateRenderObject(m_pMesh, pMat);

    AddRenderObject(m_pObj);
}
