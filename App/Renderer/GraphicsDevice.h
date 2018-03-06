#ifndef __GRAPHICS_DEVICE__
#define __GRAPHICS_DEVICE__

#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include "../html5.h"

struct ShaderProgram{};

struct GLProgram : public ShaderProgram{
    GLuint Program;
};

class GraphicsDevice
{
public:
    GraphicsDevice() {}
    void Initialize();

    ShaderProgram* CreateProgram(char* vertexShaderText, char* fragmentShaderText);

    void Clear();

protected:
    GLuint CreateShader(GLenum type, char* shaderText);

protected:
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE m_context;
};

#endif