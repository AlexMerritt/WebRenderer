#include "Renderer.h"
#include "../Util.h"


Renderer::Renderer() { }

void Renderer::Initialize()
{
    m_pDevice = new GraphicsDevice(); 
    m_pDevice->Initialize();

	// RenderObject* pObj = CreateRenderObject();
	// m_objects.push_back(pObj);

    m_pDevice->SetClearColor(0.2f, 0.5f, 0.1f);

    Log("Renderer Initialized");
}

RenderObject* Renderer::CreateRenderObject(char* vertexShaderText, char* fragmentShaderText)
{
	Shader* pShader = m_pDevice->CreateProgram(vertexShaderText, fragmentShaderText);
    
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

	return new RenderObject(pShader, pVB, pIB, iNumElements);
}

void Renderer::Resize(int iWidth, int iHeight)
{
	m_pDevice->Resize(iWidth, iHeight);
}

static float b = 0;

void Renderer::Render()
{
    m_pDevice->Clear();
    
    DrawScene(m_pScene);
}

void Renderer::DrawScene(Scene* pScene)
{
    std::string strSceneName = pScene->GetName();
    Log("Draing scene: " + strSceneName);

    // Set Camera
    Camera* pCamera = pScene->GetCamera();
    // m_pDevice->SetCamera(pScene->GetCamera());

    // get the list of render objects
    std::vector<RenderObject*> objs = pScene->GetObjects();
    printf("num objects, %d\n", (int)objs.size());

    // Draw each one
    for(unsigned int i = 0; i < objs.size(); ++i)
	{
		RenderObject* pObj = objs[i];
		m_pDevice->Render(pCamera, pObj);
	}
}