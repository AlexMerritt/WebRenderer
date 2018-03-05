#include <stdio.h>
#include <string>

#include "Application.h"
#include "Util.h"


using namespace std;

extern "C"{
    void Initialize();
    void Update();

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
