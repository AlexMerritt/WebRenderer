#include "Application.h"
#include <emscripten/emscripten.h>

void Log(std::string strText)
{
    std::string strMessage = "console.log('" + strText + "')";
    emscripten_run_script(strMessage.c_str());
}

Application::Application()
{
    Initialize();
    m_strAppName = "Renderer";
}

void Application::Initialize()
{
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
    Log("Render");
}