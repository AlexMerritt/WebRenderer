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

    std::vector<Vertex> verticies;

    verticies.push_back(Vertex(0.0, 0.0, 0.0));
    verticies.push_back(Vertex(0.0, 1.0, 0.0));
    verticies.push_back(Vertex(2.0, 0.0, 0.0));

    std::vector<unsigned int> indicies;
    indicies.push_back(0);
    indicies.push_back(1);
    indicies.push_back(2);

    Mesh mesh = Mesh(verticies, indicies);

    return CreateRenderObject(&mesh, pShader);
}

RenderObject* Renderer::CreateRenderObject(Mesh* pMesh, Shader* pShader)
{
    std::vector<Vertex>& verts = pMesh->GetVerticies();

    BufferData* vbd = new BufferData(verts.data(), verts.size(), sizeof(Vertex));
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