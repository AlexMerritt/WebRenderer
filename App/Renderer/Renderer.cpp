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

    Shader* pShader = m_pDevice->CreateProgram(vShaderStr, fShaderStr);
    
	unsigned int iNumElements = 3;

    float verts[] = {
        0.0, 0.5, 0.0,
        -0.5, -0.5, 0.0,
        0.5, -0.5, 0.0
    };

    int inds[] = {
        0, 1, 2
    };

    BufferData* vbd = new BufferData(verts, iNumElements, 3 * sizeof(float));
    VertexBuffer* pVB = m_pDevice->CreateVertexBuffer(vbd);

    BufferData* idb = new BufferData(inds, iNumElements, sizeof(unsigned int));
    Buffer* pIB = m_pDevice->CreateIndexBuffer(idb);

	m_pObj = new RenderObject(pShader, pVB, pIB, iNumElements);

    Log("Renderer Initialized");
}

static float b = 0;

void Renderer::DrawScene()
{
	
	b += 0.1f;
	if (b > 1.0f) {
		b = 0;
	}

	m_pDevice->SetClearColor(0.2f, 0.0f, b);

    Log("Renderer Draw Scene");

    m_pDevice->Clear();

     m_pDevice->Render(m_pObj);
}