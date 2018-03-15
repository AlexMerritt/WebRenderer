#ifndef __GRAPHICS_DEVICE__
#define __GRAPHICS_DEVICE__

#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <emscripten/html5.h>

#include "Shader.h"

#include "../Graphics/Buffer.h"
#include "../Graphics/RenderObject.h"
#include "../Graphics/Camera.h"

#include "../Math/Matrix.h"

#include <string>

class GraphicsDevice
{
public:
    GraphicsDevice() {}
    void Initialize();

    Shader* CreateProgram(char* vertexShaderText, char* fragmentShaderText);
    VertexBuffer* CreateVertexBuffer(VertexBufferData* pData);
    Buffer* CreateIndexBuffer(BufferData* pData);

    // void Draw(Buffer* pVB, Buffer* pIB, ShaderProgram* pProgram);
    // void Render(Shader* pProgram, VertexBuffer* pVertBuffer, Buffer* pIndexBuffer);
    void Render(Camera* pCamera, RenderObject* pRO);

    void SetClearColor(float r, float g, float b);

    void Clear();

	void Resize(int iWidth, int iHeight);

protected:
    GLuint CreateShader(GLenum type, char* shaderText);

    void SetUniformMatrix(Shader* shader, const std::string& param, Matrix4 km);

protected:
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE m_context;
};

#endif