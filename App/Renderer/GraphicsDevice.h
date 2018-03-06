#ifndef __GRAPHICS_DEVICE__
#define __GRAPHICS_DEVICE__

#include "../html5.h"

class GraphicsDevice
{
public:
    GraphicsDevice() {}
    void Initialize();

    void Clear();

protected:
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE m_context;
};

#endif