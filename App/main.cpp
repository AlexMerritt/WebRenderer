#include <stdio.h>
#include <string>

#include "Application.h"
#include "Util.h"


using namespace std;

extern "C"{
    void Initialize();
    void Update();
	void Resize(int iWidth, int iHeight);

}

Application* pApplication = 0;

void Initialize()
{
    if(!pApplication)
    {
        pApplication = new Application();
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
