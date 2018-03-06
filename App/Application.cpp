#include "Application.h"
#include "Util.h"
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include "html5.h"

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
    EmscriptenWebGLContextAttributes contextAttrs;
    EmscriptenWebGLContextAttributes attribs;
    emscripten_webgl_init_context_attributes(&attribs);
    attribs.alpha = false;
    attribs.enableExtensionsByDefault = false;
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context =  emscripten_webgl_create_context("display", &attribs);
    emscripten_webgl_make_context_current(context);

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