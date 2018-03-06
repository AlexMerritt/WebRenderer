#ifndef __APPLICATION__
#define __APPLICATION__

#include "Renderer/GraphicsDevice.h"

#include <string>

class Application{
public:
    Application();

    void Initialize();
    void Frame();

protected:
    void Update();
    void Render();

protected:
    std::string m_strAppName;
    GraphicsDevice* m_pGraphicsDevice;
};

#endif