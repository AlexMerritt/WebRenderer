#ifndef __APPLICATION__
#define __APPLICATION__

#include "Renderer/Renderer.h"
#include "Graphics/Scene.h"
#include "Util/Input.h"

#include "html5.h"

#include <string>

class Application{
public:
    Application(int iWidth, int iHeight);

    void Initialize();
    void Frame();

	void OnResize(int iWidth, int iHeight);

    void KeyDown(const EmscriptenKeyboardEvent* e);
    void KeyUp(const EmscriptenKeyboardEvent* e);

protected:
    void Update();
    void Render();

protected:
    std::string m_strAppName;
    Renderer* m_pRenderer;

    Scene* m_pScene;

    int m_iWindowWidth;
    int m_iWindowHeight;

    Keyboard* m_pKeyboard;
};

#endif