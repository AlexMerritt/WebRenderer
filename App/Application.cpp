#include "Application.h"
#include "Util.h"
#include <emscripten/emscripten.h>
#include "Graphics/Scene.h"


EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context;

void output_error(int error, const char* msg)
{
    std::string strError = std::to_string((long long)error) + " " + std::string(msg);
    Log(strError);
}

Application::Application()
{
    Initialize();
    m_strAppName = "Renderer";
}

void Application::Initialize()
{

	int iWidth = 640;
	int iHeight = 480;

    m_pRenderer = new Renderer();
    m_pRenderer->Initialize();

    Log("Creating scene");

    Scene* pScene = new Scene("Test Scene");
    RenderObject* pRO = m_pRenderer->CreateRenderObject();
    pScene->AddRenderObject(pRO);

    m_pRenderer->SetScene(pScene);

    Log("Application Initalized");
}

void Application::Frame()
{
    std::string strMessage = "Processing Frame for applcation: " + m_strAppName;
    Log(strMessage);

    Update();
    Render();
}

void Application::Update()
{
    Log("Update");
}

void Application::Render()
{
    m_pRenderer->Render();
}

void Application::OnResize(int iWidth, int iHeight)
{
	m_pRenderer->Resize(iWidth, iHeight);
}