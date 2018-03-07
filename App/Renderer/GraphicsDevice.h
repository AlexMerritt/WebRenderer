#ifndef __GRAPHICS_DEVICE__
#define __GRAPHICS_DEVICE__

#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include "../html5.h"

#include "Buffer.h"

struct ShaderProgram{};

struct GLProgram : public ShaderProgram
{
    GLuint Program;
};

// struct Buffer {};

// struct GLBuffer
// {
//     GLuint Buffer;
//     int NumVerts;
// };

class GraphicsDevice
{
public:
    GraphicsDevice() {}
    void Initialize();

    ShaderProgram* CreateProgram(char* vertexShaderText, char* fragmentShaderText);
    VertexBuffer* CreateVertexBuffer(BufferData* pData);
    Buffer* CreateIndexBuffer(BufferData* pData);

    // void Draw(Buffer* pVB, Buffer* pIB, ShaderProgram* pProgram);
    void Render(ShaderProgram* pProgram, VertexBuffer* pVertBuffer, Buffer* pIndexBuffer);

    void Clear();

protected:
    GLuint CreateShader(GLenum type, char* shaderText);

protected:
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE m_context;
};

#endif