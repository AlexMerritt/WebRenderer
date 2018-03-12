#ifndef __MATERIAL__
#define __MATERIAL__

#include "../Renderer/Shader.h"

class Material
{
public:
    Material(Shader* pShader)
    {
        m_pShader = pShader;
    }

    Shader* GetShader() { return m_pShader; }

protected:
    Shader* m_pShader;

    // Shader params
};

#endif