#ifndef __SCENE__
#define __SCENE__

#include "RenderObject.h"
#include "Camera.h"
#include "../Util/Json.h"

#include <vector>
#include <string>

class Scene
{
public:
    Scene(const std::string& strSceneName, int iWindowWidth, int iWindowHeight);
    ~Scene() {}

    void Update(double dDelta);

    void AddRenderObject(RenderObject* pObj) { m_renderObjects.push_back(pObj); }

    std::vector<RenderObject*>& GetObjects() { return m_renderObjects; }
    Camera* GetCamera() const { return m_pCamera; }

    const std::string& GetName() const { return m_strSceneName; }

    void Resize(int iWindowWidth, int iWindowHeight);

protected:
    void UpdateCameras(int iWindowWidth, int iWindowHeight);

    void CreateModel();
    void CreateTest();

protected:
    std::string m_strSceneName;
    std::vector<RenderObject*> m_renderObjects;
    Camera* m_pCamera;
};

#endif