#ifndef __GRAPHICS_DEVICE__
#define __GRAPHICS_DEVICE__

#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include "../html5.h"

#include "../Graphics/Buffer.h"
#include "../Graphics/Shader.h"
#include "../Graphics/RenderObject.h"

class GraphicsDevice
{
public:
    GraphicsDevice() {}
    void Initialize();

    Shader* CreateProgram(char* vertexShaderText, char* fragmentShaderText);
    VertexBuffer* CreateVertexBuffer(BufferData* pData);
    Buffer* CreateIndexBuffer(BufferData* pData);

    // void Draw(Buffer* pVB, Buffer* pIB, ShaderProgram* pProgram);
    // void Render(Shader* pProgram, VertexBuffer* pVertBuffer, Buffer* pIndexBuffer);
    void Render(RenderObject* pRO);

    void SetClearColor(float r, float g, float b);

    void Clear();

	void Resize(int iWidth, int iHeight);

protected:
    GLuint CreateShader(GLenum type, char* shaderText);

protected:
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE m_context;
};

#endif