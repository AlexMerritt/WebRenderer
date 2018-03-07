#include "GraphicsDevice.h"
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include "../Util.h"
#include <vector>


#define HASERROR() HasError(__LINE__, __FILE__)

inline bool HasError(int line, const char* file)
{
	GLenum err;
	err = glGetError();
	bool rtn = false;
	while (err != GL_NO_ERROR)
	{
		Log("Line: " + std::to_string(line) + " " + file);
		switch (err)
		{
		case GL_INVALID_ENUM:
			Log("An unacceptable value is specified for an enumerated argument");
			break;
		case GL_INVALID_VALUE:
			Log("A numeric argument is out of range");
			break;
		case GL_INVALID_OPERATION:
			Log("The specified operation is not allowed in the current state");
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			Log("The framebuffer object is not complete");
			break;
		case GL_OUT_OF_MEMORY:
			Log("There is not enough memory left to execute the command");
			break;

		}
		err = glGetError();
		rtn = true;
	}

	//Assert(rtn == false);
	return rtn;
}


void GraphicsDevice::Initialize()
{
    EmscriptenWebGLContextAttributes attribs;
    emscripten_webgl_init_context_attributes(&attribs);
    attribs.alpha = false;
    attribs.enableExtensionsByDefault = false;
    attribs.majorVersion = 2;
    attribs.minorVersion = 0;

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
                std::vector<char> v(infoLen);
                glGetShaderInfoLog(shader, infoLen, NULL, v.data());
                std::string s(begin(v), end(v));

                Log(std::to_string((long long)infoLen));
                
                printf("%s\n", s.c_str());  
            }
        }
    }
    else
    {
        Log("Shader not created");
    }

    return shader;
}

Buffer* GraphicsDevice::CreateVertexBuffer(float* vertices, int iNumVerts)
{
    GLuint vb;

    glGenBuffers(1,&vb);
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * iNumVerts, vertices, GL_DYNAMIC_DRAW);

    HASERROR();

    GLBuffer* pBuffer = new GLBuffer();
    pBuffer->NumVerts = iNumVerts;
    pBuffer->Buffer = vb;

    return (Buffer*)pBuffer;
}

Buffer* GraphicsDevice::CreateIndexBuffer(int* indices, int iNumInds)
{
    GLuint ib;

    glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, iNumInds * sizeof(int), indices, GL_DYNAMIC_DRAW);

    GLBuffer* pBuffer = new GLBuffer();
    pBuffer->NumVerts = iNumInds;
    pBuffer->Buffer = ib;

    return (Buffer*)pBuffer;
}

void GraphicsDevice::Draw(Buffer* pBuffer, ShaderProgram* pProgram)
{
    GLProgram* pPro = (GLProgram*)pProgram;
    GLBuffer* pVB = (GLBuffer*)pBuffer;
    glUseProgram(pPro->Program);
}

void GraphicsDevice::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}