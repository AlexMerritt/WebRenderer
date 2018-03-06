#include "Application.h"
#include "Util.h"


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
    m_pRenderer = new Renderer();
    m_pRenderer->Initialize();

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
    m_pRenderer->DrawScene();
}