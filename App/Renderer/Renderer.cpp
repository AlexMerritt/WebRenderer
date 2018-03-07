#include "Renderer.h"
#include "../Util.h"

char vShaderStr[] =
      "#version 300 es                          \n"
      "layout(location = 0) in vec4 vPosition;  \n"
      "void main()                              \n"
      "{                                        \n"
      "   gl_Position = vPosition;              \n"
      "}                                        \n";

char fShaderStr[] =
    "#version 300 es                              \n"
    "precision mediump float;                     \n"
    "out vec4 fragColor;                          \n"
    "void main()                                  \n"
    "{                                            \n"
    "   fragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );  \n"
    "}                                            \n";

Renderer::Renderer() { }

void Renderer::Initialize()
{
    m_pDevice = new GraphicsDevice(); 
    m_pDevice->Initialize();

    m_pProgram = m_pDevice->CreateProgram(vShaderStr, fShaderStr);
    float verts[] = {
        0.0, 0.5, 0.0,
        -0.5, -0.5, 0.0,
        0.5, -0.5, 0.0
    };

    int inds[] = {
        0, 1, 2
    };
    BufferData* vbd = new BufferData(verticies, numVerts, sizeof(Vector4));
    BufferData* ibd = new BufferData(inds, numInds, sizeof(unsigned int));

    Log("Renderer Initialized");
}

void Renderer::DrawScene()
{
    Log("Renderer Draw Scene");

    m_pDevice->Clear();
}