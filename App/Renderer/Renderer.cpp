#include "Renderer.h"
#include "../Util.h"


Renderer::Renderer() { }

void Renderer::Initialize()
{
    m_pDevice = new GraphicsDevice(); 
    m_pDevice->Initialize();

    m_pDevice->SetClearColor(0.05f, 0.1f, 0.05f);

    Log("Renderer Initialized");
}

RenderObject* Renderer::CreateRenderObject(Mesh* pMesh, char* vertexShaderText, char* fragmentShaderText)
{
    Shader* pShader = m_pDevice->CreateProgram(vertexShaderText, fragmentShaderText);
    std::vector<Vertex>& verts = pMesh->GetVerticies();

    VertexBufferData* vbd = new VertexBufferData(verts.data(), verts.size(), pMesh->GetVertexElementSize(), pMesh->GetAttributes());
    VertexBuffer* pVB = m_pDevice->CreateVertexBuffer(vbd);

    std::vector<unsigned int> inds = pMesh->GetIndicies();

    BufferData* idb = new BufferData(inds.data(), inds.size(), sizeof(unsigned int));
    Buffer* pIB = m_pDevice->CreateIndexBuffer(idb);

    return new RenderObject(pShader, pVB, pIB, inds.size());
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

    // Set Camera
    Camera* pCamera = pScene->GetCamera();
    // m_pDevice->SetCamera(pScene->GetCamera());

    // get the list of render objects
    std::vector<RenderObject*> objs = pScene->GetObjects();

    // Draw each one
    for(unsigned int i = 0; i < objs.size(); ++i)
	{
		RenderObject* pObj = objs[i];
		m_pDevice->Render(pCamera, pObj);
	}
}