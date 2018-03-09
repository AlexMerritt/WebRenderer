#ifndef __SCENE__
#define __SCENE__

#include "RenderObject.h"
#include "Camera.h"

#include <vector>
#include <string>

class Scene
{
public:
    Scene(const std::string& strSceneName);
    ~Scene() {}

    void AddScene(){}

    std::vector<RenderObject*> GetObjects() const { return m_renderObjects; }
    Camera* GetCamera() const { return m_pCamera; }

protected:
    std::string m_strSceneName;
    std::vector<RenderObject*> m_renderObjects;
    Camera* m_pCamera;
};

#endif