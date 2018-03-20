#ifndef __SHADER_PROGRAM__
#define __SHADER_PROGRAM__

#include <string>
#include <map>

struct ShaderSource
{
    ShaderSource(const std::string& strVertexSource, const std::string& strFragmentSource)
    {
        VertexShaderSource  = strVertexSource;
        FragmentShaderSource = strFragmentSource;
    }

    std::string VertexShaderSource;
    std::string FragmentShaderSource;
};

// Shader Sources
static const std::string strColorVertex =
    "#version 300 es                                         \n"
    "in vec4 inputPosition;             \n"
    "in vec4 inputColor;                \n"
    "uniform mat4 ViewMatrix;                                \n"
    "uniform mat4 ProjectionMatrix;                          \n"
    "out vec3 color;                                         \n"
    "void main(void)                                         \n"
    "{                                                       \n"
    "    gl_Position = ViewMatrix * inputPosition;           \n"
    "    gl_Position = ProjectionMatrix * gl_Position;       \n"
    "    color = inputColor.xyz;                             \n"
    "}";

static const std::string strColorFragment =
    "#version 300 es                              \n"
    "precision mediump float;                     \n"
    "in vec3 color;                               \n"
    "out vec4 fragColor;                          \n"
    "void main()                                  \n"
    "{                                            \n"
    "   fragColor = vec4 ( color, 1.0 );  \n"
    "}                                            \n";

// Shader Names
static const std::string COLOR_SHADER = "ColorShader";

// Shader mapping
static std::map<std::string, ShaderSource*> s_shaderSource = {
    {COLOR_SHADER, new ShaderSource(strColorVertex, strColorFragment)}
};


#endif