#include "GraphicsDevice.h"
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include "../Util.h"



void GraphicsDevice::Initialize()
{
    EmscriptenWebGLContextAttributes contextAttrs;
    EmscriptenWebGLContextAttributes attribs;
    emscripten_webgl_init_context_attributes(&attribs);
    attribs.alpha = false;
    attribs.enableExtensionsByDefault = false;
    m_context =  emscripten_webgl_create_context("display", &attribs);
    emscripten_webgl_make_context_current(m_context);

    glClearColor(0.1, 0.2, 0.4, 1.0);

    Log("Graphics Device Initialized");
}

ShaderProgram* GraphicsDevice::CreateProgram(char* vertexShaderText, char* fragmentShaderText)
{
    GLProgram* pResult = 0;

    GLuint vertexShader;
    GLuint fragmentShader;

    vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderText);
    fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderText);

    GLuint program = glCreateProgram();

    if(program){
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);


        glLinkProgram(program);

        pResult = new GLProgram();
        pResult->Program = program;
    }

    return pResult;
}

GLuint GraphicsDevice::CreateShader(GLenum type, char* shaderText)
{
    GLuint shader = 0;

    shader = glCreateShader(type);

    if(shader)
    {
        glShaderSource(shader, 1, &shaderText, NULL);
        glCompileShader(shader);

        GLint compiled;

        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

        if(!compiled)
        {
            GLint infoLen = 0;
            glGetShaderiv ( shader, GL_INFO_LOG_LENGTH, &infoLen );

            if ( infoLen > 1 )
            {
                char infoLog[infoLen];

                // And print them out
                glGetShaderInfoLog(shader, infoLen, NULL, infoLog );
                Log(std::to_string((long long)infoLen));
                
                std::string strError = std::string(infoLog) + "\0";
                Log(strError);

                
            }
        }
    }
    else
    {
        Log("Shader not created");
    }

    return shader;
}

void GraphicsDevice::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}