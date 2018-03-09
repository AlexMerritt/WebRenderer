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

void Initialize(int iWidth, int iHeight)
{
    if(!pApplication)
    {
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
