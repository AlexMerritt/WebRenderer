#ifndef __MATERIAL__
#define __MATERIAL__

#include "../Renderer/Shader.h"

#include <map>
#include <string>   

enum ParameterType
{
    eFloat
};

struct ShaderParameter
{
    std::string ParameterName;
    void* Value;
    ParameterType Type;
    int Size;

};

class Material
{

public:
    Material(Shader* pShader)
    {
        m_pShader = pShader;
    }

    Shader* GetShader() { return m_pShader; }

    void SetParameter(ShaderParameter* pParam) { m_parameters[pParam->ParameterName] = pParam;}
    ShaderParameter* GetParameter(std::string strParameter)
    {
        ShaderParameter* pResult = 0;

        if(m_parameters.find(strParameter) != m_parameters.end())
        {
            pResult = m_parameters[strParameter];
        }

        return pResult;
    }

    std::map<std::string, ShaderParameter*> GetParameters() { return m_parameters; }

protected:
    Shader* m_pShader;

    std::map<std::string, ShaderParameter*> m_parameters; // Switch this to a vector so that I have faster iteration when setting the values


};

#endif