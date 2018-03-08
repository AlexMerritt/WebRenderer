#ifndef __APPLICATION__
#define __APPLICATION__

#include "Renderer/Renderer.h"

#include <string>

class Application{
public:
    Application();

    void Initialize();
    void Frame();

	void OnResize(int iWidth, int iHeight);

protected:
    void Update();
    void Render();

protected:
    std::string m_strAppName;
    Renderer* m_pRenderer;
};

#endif