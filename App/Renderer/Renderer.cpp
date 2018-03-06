#include "Renderer.h"
#include "../Util.h"

Renderer::Renderer() { }

void Renderer::Initialize()
{
    m_pDevice = new GraphicsDevice(); 
    m_pDevice->Initialize();

    Log("Renderer Initialized");
}

void Renderer::DrawScene()
{
    Log("Renderer Draw Scene");

    m_pDevice->Clear();
}