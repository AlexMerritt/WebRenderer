#include <stdio.h>
#include <string>

#include "Application.h"
#include "Util.h"

extern "C"{
    void Initialize(int iWidth, int iHeight);
    void Update();
	void Resize(int iWidth, int iHeight);

}

Application* pApplication = 0;

static EM_BOOL KeyDown(int eventType, const EmscriptenKeyboardEvent *e, void *userData)
{
    // unsigned long charCode = e->charCode;
    // unsigned long keyCode = e->keyCode;
    // unsigned long which = e->which;
    // unsigned long loc = e->location;
    // printf("Key down event\nChar: %d, Key: %d, Which: %d, Location: %d\n", (int)charCode, (int)keyCode, (int)which, (int)loc);

    pApplication->KeyDown(e);
    return 0;
}

static EM_BOOL KeyUp(int eventType, const EmscriptenKeyboardEvent *e, void *userData)
{
    pApplication->KeyUp(e);
    return 0;

}

static EM_BOOL MouseEvent(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData)
{
    pApplication->MouseEvent(mouseEvent);
    return 0;
}

void Initialize(int iWidth, int iHeight)
{
    if(!pApplication)
    {
        emscripten_set_keydown_callback(0,0,1, KeyDown);
        emscripten_set_keyup_callback(0,0, 1, KeyUp);
        emscripten_set_mousemove_callback(0,0,1,MouseEvent);
        emscripten_set_mousedown_callback(0,0,1, MouseEvent);
        emscripten_set_mouseup_callback(0,0,1,MouseEvent);


        pApplication = new Application(iWidth, iHeight);
    }
    else
    {
        Log("Application already initialized");
    }
}

void Update()
{
    pApplication->Frame();
}

void Resize(int iWidth, int iHeight)
{
	pApplication->OnResize(iWidth, iHeight);
}
