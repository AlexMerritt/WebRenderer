#include <stdio.h>
#include <string>

#include "Application.h"
#include "Util.h"
#include <emscripten/html5.h>
#include <emscripten/emscripten.h>

extern "C"{
    void Initialize(int iWidth, int iHeight);
    void Update();
	void Resize(int iWidth, int iHeight);

}

static EM_BOOL KeyDown(int eventType, const EmscriptenKeyboardEvent *e, void *userData)
{
    // unsigned long charCode = e->charCode;
    // unsigned long keyCode = e->keyCode;
    // unsigned long which = e->which;
    // unsigned long loc = e->location;
    // printf("Key down event\nChar: %d, Key: %d, Which: %d, Location: %d\n", (int)charCode, (int)keyCode, (int)which, (int)loc);

    Application::Get()->KeyDown(e);
    return 0;
}

static EM_BOOL KeyUp(int eventType, const EmscriptenKeyboardEvent *e, void *userData)
{
    Application::Get()->KeyUp(e);
    return 0;

}

static EM_BOOL MouseEvent(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData)
{
    Application::Get()->MouseEvent(mouseEvent);
    return 0;
}

void Initialize(int iWidth, int iHeight)
{
    if(!Application::Get())
    {
        emscripten_set_keydown_callback(0,0,1, KeyDown);
        emscripten_set_keyup_callback(0,0, 1, KeyUp);
        emscripten_set_mousemove_callback(0,0,1,MouseEvent);
        emscripten_set_mousedown_callback(0,0,1, MouseEvent);
        emscripten_set_mouseup_callback(0,0,1,MouseEvent);

        Application::Initialize(iWidth, iHeight);
    }
    else
    {
        Log("Application already initialized");
    }
}

double dLastTime = 0;


void Frame()
{
    double dCurrentTime = emscripten_get_now() / 1000.0;

    double dDelta = dCurrentTime - dLastTime;
    dLastTime = dCurrentTime;

    Application::Get()->Frame(dDelta);

}

void Update()
{
    // pApplication->Frame();
    emscripten_set_main_loop(Frame, 0, 0);
}

void Resize(int iWidth, int iHeight)
{
	Application::Get()->OnResize(iWidth, iHeight);
}
