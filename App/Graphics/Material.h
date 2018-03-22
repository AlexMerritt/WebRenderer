#ifndef __MATERIAL__
#define __MATERIAL__

#include "../Renderer/Shader.h"

#include <map>
#include <string>   

struct Parameter
{
    std::string Name;
};

struct TextureParameter : Parameter
{
    //TextureHandle value;
};

struct FloatParameter : Parameter
{
    std::vector<float> Value;
};

struct IntParameter : Parameter
{
    std::vector<int> Value;
};

class Material
{

public:
    Material(Shader* pShader)
    {
        m_pShader = pShader;
    }

    Shader* GetShader() { return m_pShader; }

    void SetFloatParam(FloatParameter* pParam)
    {
        FloatParameter* pCurrentParam = GetFloatParam(pParam->Name);
        // If it does not exists
        if(!pCurrentParam)
        {
            m_floatParams.push_back(pParam);
        }
        else
        {
            pCurrentParam->Value = pParam->Value;
        }
    }

    FloatParameter* GetFloatParam(std::string strParameterName)
    {
        FloatParameter* pResult = 0;

        for(int i = 0; i < m_floatParams.size(); ++i)
        {
            FloatParameter* pCurrentParam = m_floatParams[i];
            if(pCurrentParam->Name == strParameterName)
            {
                pResult = pCurrentParam;

            }
        }

        return pResult;
    }


    std::vector<FloatParameter*>& GetFloatParams() { return m_floatParams; }
protected:
    Shader* m_pShader;

    std::vector<FloatParameter*> m_floatParams;
    std::vector<IntParameter*> m_intParams;
    std::vector<TextureParameter*> m_textureParams;
};

#endif