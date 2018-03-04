#include <stdio.h>
#include <emscripten/emscripten.h>
#include <string>
#include "Application.h"

using namespace std;

extern "C"{
    void Initialize();
    void Update();

}

Application* pApplication = 0;

void Initialize(){
    pApplication = new Application();
}

void Update(){
    pApplication->Frame();
}
