#ifndef __APPLICATION__
#define __APPLICATION__

#include "Renderer/Renderer.h"
#include "Graphics/Scene.h"

#include <string>

class Application{
public:
    Application(int iWidth, int iHeight);

    void Initialize();
    void Frame();

	void OnResize(int iWidth, int iHeight);

protected:
    void Update();
    void Render();

protected:
    std::string m_strAppName;
    Renderer* m_pRenderer;

    Scene* m_pScene;

    int m_iWindowWidth;
    int m_iWindowHeight;
};

#endif