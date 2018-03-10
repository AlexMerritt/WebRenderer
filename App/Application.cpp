#include "Application.h"
#include "Util.h"
#include <emscripten/emscripten.h>
#include "Graphics/Scene.h"
#include "Graphics/ShaderPrograms.h"


EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context;

void output_error(int error, const char* msg)
{
    std::string strError = std::to_string((long long)error) + " " + std::string(msg);
    Log(strError);
}

Application::Application(int iWidth, int iHeight)
{
    m_iWindowWidth = iWidth;
    m_iWindowHeight = iHeight;

    printf("Initializing window to %d, %d\n", m_iWindowWidth, m_iWindowHeight);

    Initialize();
    m_strAppName = "Renderer";
}

void Application::Initialize()
{
    m_pKeyboard = new Keyboard();
    Keyboard::Set(m_pKeyboard);

    m_pMouse = new Mouse();
    Mouse::Set(m_pMouse);

    m_pRenderer = new Renderer();
    m_pRenderer->Initialize();

    Log("Creating scene");

    m_pScene = new Scene("Test Scene", m_iWindowWidth, m_iWindowHeight);
    RenderObject* pRO = m_pRenderer->CreateRenderObject(vs, fShaderStr);
    m_pScene->AddRenderObject(pRO);

    m_pRenderer->SetScene(m_pScene);

    Log("Application Initalized");
}

void Application::KeyDown(const EmscriptenKeyboardEvent* e)
{
    m_pKeyboard->KeyDown(e->keyCode);
}

void Application::KeyUp(const EmscriptenKeyboardEvent* e)
{
    m_pKeyboard->KeyUp(e->keyCode);
}

void Application::MouseEvent(const EmscriptenMouseEvent* e)
{
    Log("Mouse event\n");
}

void Application::Frame()
{
    Update();
    Render();
}

void Application::Update()
{
    m_pScene->Update();

    m_pKeyboard->Update();
}

void Application::Render()
{
    m_pRenderer->Render();
}

void Application::OnResize(int iWidth, int iHeight)
{
    m_iWindowWidth = iWidth;
    m_iWindowHeight = iHeight;

    printf("Resizing window to %d, %d\n", m_iWindowWidth, m_iWindowHeight);

    m_pScene->Resize(iWidth, iHeight);
	m_pRenderer->Resize(iWidth, iHeight);
}