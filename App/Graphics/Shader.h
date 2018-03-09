#ifndef __SHADER__
#define __SHADER__

class Shader
{
public:
    Shader(unsigned int shader) : m_shader(shader) {}

    const unsigned int GetShader() { return m_shader; }

protected:
    unsigned int m_shader;
};

#endif