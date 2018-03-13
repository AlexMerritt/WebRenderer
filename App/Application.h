#ifndef __APPLICATION__
#define __APPLICATION__

#include "Renderer/Renderer.h"
#include "Graphics/Scene.h"
#include "Util/Input.h"
#include <emscripten/html5.h>

#include <string>

class Application {
public:
    static void Initialize(int iWidth, int iHeight);
    static Application* Get();

public:
    void Frame(double dDelta);

	void OnResize(int iWidth, int iHeight);

    void KeyDown(const EmscriptenKeyboardEvent* e);
    void KeyUp(const EmscriptenKeyboardEvent* e);
    void MouseEvent(const EmscriptenMouseEvent* e);

    Renderer* GetRenderer() { return m_pRenderer; }

protected:
    Application(int iWidth, int iHeight);

    void Startup();
    void CreateSystems();

    void Update(double dDelta);
    void Render();

protected:
    std::string m_strAppName;
    Renderer* m_pRenderer;

    Scene* m_pScene;

    int m_iWindowWidth;
    int m_iWindowHeight;

    Keyboard* m_pKeyboard;
    Mouse* m_pMouse;
};

#endif