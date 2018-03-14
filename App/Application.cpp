#include "Application.h"
#include "Util.h"
#include "Graphics/Scene.h"
#include "ServiceProvider.h"

Application* s_pApplication = 0;

void Application::Initialize(int iWidth, int iHeight)
{
    s_pApplication = new Application(iWidth, iHeight);
    s_pApplication->Startup();
}

Application* Application::Get()
{
    return s_pApplication;
}

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

    m_strAppName = "Renderer";
}

void Application::Startup()
{
    CreateSystems();

    Log("Creating scene");

    m_pScene = new Scene("Test Scene", m_iWindowWidth, m_iWindowHeight);


    m_pRenderer = Systems::Get<Renderer>();
    m_pRenderer->SetScene(m_pScene);

    Log("Application Initalized");
}

void Application::CreateSystems()
{
    m_pRenderer = new Renderer();
    Systems::Register<Renderer>(m_pRenderer);

    m_pKeyboard = new Keyboard();
    Keyboard::Set(m_pKeyboard);

    m_pMouse = new Mouse();
    Mouse::Set(m_pMouse);

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
}

void Application::Frame(double dDelta)
{
    if(false)
    {
        static double dAccumalation = 0;
        static int iFrames = 0;

        dAccumalation += dDelta;
        ++iFrames;

        if(dAccumalation >= 1.0)
        {
            printf("%d\n", iFrames);
            iFrames = 0;
            dAccumalation = 0.0;
        }
    }


    Update(dDelta);
    Render();
}

void Application::Update(double dDelta)
{
    m_pScene->Update(dDelta);
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