#include "Renderer.h"
#include "../Util.h"
#include "../Graphics/ShaderPrograms.h"


Renderer::Renderer() { }

void Renderer::Initialize()
{
    m_pDevice = new GraphicsDevice(); 
    m_pDevice->Initialize();

    m_pDevice->SetClearColor(0.05f, 0.1f, 0.05f);

    Log("Renderer Initialized");
}

RenderObject* Renderer::CreateRenderObject(Mesh* pMesh, const std::string& vertexShaderText, const std::string& fragmentShaderText)
{
    Shader* pShader = m_pDevice->CreateProgram(vertexShaderText.c_str(), fragmentShaderText.c_str());
    std::vector<Vertex>& verts = pMesh->GetVerticies();

    VertexBufferData* vbd = new VertexBufferData(verts.data(), verts.size(), pMesh->GetVertexElementSize(), pMesh->GetAttributes());
    VertexBuffer* pVB = m_pDevice->CreateVertexBuffer(vbd);

    std::vector<unsigned int> inds = pMesh->GetIndicies();

    BufferData* idb = new BufferData(inds.data(), inds.size(), sizeof(unsigned int));
    Buffer* pIB = m_pDevice->CreateIndexBuffer(idb);

    delete vbd;
    delete idb;

    return new RenderObject(new Material(pShader), pVB, pIB, inds.size());
}

RenderObject* Renderer::CreateRenderObject(Mesh* pMesh, Material* pMaterial)
{
    std::vector<Vertex>& verts = pMesh->GetVerticies();

    VertexBufferData* vbd = new VertexBufferData(verts.data(), verts.size(), pMesh->GetVertexElementSize(), pMesh->GetAttributes());
    VertexBuffer* pVB = m_pDevice->CreateVertexBuffer(vbd);

    std::vector<unsigned int> inds = pMesh->GetIndicies();

    BufferData* idb = new BufferData(inds.data(), inds.size(), sizeof(unsigned int));
    Buffer* pIB = m_pDevice->CreateIndexBuffer(idb);

    delete vbd;
    delete idb;

    return new RenderObject(pMaterial, pVB, pIB, inds.size());
}


Material* Renderer::CreateMaterial(std::string strShaderName)
{
    Shader* pShader = 0;

    if(m_loadedShaders.find(strShaderName) != m_loadedShaders.end())
    {
        pShader = m_loadedShaders[strShaderName];
    }
    else
    {
        // Find the shader source
        if(s_shaderSource.find(strShaderName) != s_shaderSource.end())
        {
            printf("Creating shader \"%s\"\n", strShaderName.c_str());
            ShaderSource* shaderSrc = s_shaderSource[strShaderName];

            pShader = m_pDevice->CreateProgram(shaderSrc->VertexShaderSource.c_str(), shaderSrc->FragmentShaderSource.c_str());
            m_loadedShaders[strShaderName] = pShader;
        }
        else
        {
            printf("Error: Shader - %s does not exist", strShaderName.c_str());
        }
    }

    return new Material(pShader);
}

void Renderer::Update(RenderObject* pObj, Mesh* pMesh)
{
    std::vector<Vertex>& verts = pMesh->GetVerticies();
    VertexBufferData* vbd = new VertexBufferData(verts.data(), verts.size(), pMesh->GetVertexElementSize(), pMesh->GetAttributes());

    m_pDevice->UpdateBuffer(pObj->GetVertexBuffer(), vbd);
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