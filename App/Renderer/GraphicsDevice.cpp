#include "GraphicsDevice.h"
#include "../Util.h"
#include "../Graphics/Material.h"
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

    Log("Graphics Device Initialized");
}

Shader* GraphicsDevice::CreateProgram(const char* vertexShaderText, const char* fragmentShaderText)
{
    Shader* pResult = 0;

    GLuint vertexShader;
    GLuint fragmentShader;

    vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderText);
    fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderText);

    GLuint program = glCreateProgram();

    if(program){
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        
        glLinkProgram(program);

        pResult = new Shader(program);
    }

    return pResult;
}

GLuint GraphicsDevice::CreateShader(GLenum type, const char* shaderText)
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

VertexBuffer* GraphicsDevice::CreateVertexBuffer(VertexBufferData* pData)
{
    GLuint vertexArray;
    GLuint vb;

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    glGenBuffers(1, &vb);

    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, pData->GetBufferSize(), pData->GetData(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    HASERROR();

    glBindBuffer(GL_ARRAY_BUFFER, vb);

    std::vector<VertexAttribute> attributes = pData->GetAttributes();

    unsigned int iAttributeStartPosition = 0;

    for(unsigned int i = 0; i < attributes.size(); ++i)
    {
        VertexAttribute attribute = attributes[i];

        unsigned int iNumFloats = attribute.Stride / sizeof(float); // Maybe some day include this size in the attribute

        glEnableVertexAttribArray(i);

        glVertexAttribPointer(i, iNumFloats, GL_FLOAT, false, pData->GetElementSize(), (unsigned char*)0 + iAttributeStartPosition);

        iAttributeStartPosition += attribute.Stride;
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    HASERROR();

    return new VertexBuffer(vertexArray, vb, pData->GetNumElements(), pData->GetElementSize());
}

Buffer* GraphicsDevice::CreateIndexBuffer(BufferData* pData)
{
    GLuint ib;


    glGenBuffers(1, &ib);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, pData->GetBufferSize(), pData->GetData(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    HASERROR();

    return new Buffer(ib, pData->GetNumElements(), pData->GetElementSize());
}

void GraphicsDevice::UpdateBuffer(Buffer* pBuffer, BufferData* pData)
{
    GLuint buffer = pBuffer->GetBuffer();

    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, pData->GetBufferSize(), pData->GetData(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GraphicsDevice::SetUniformMatrix(Shader* pShader, const std::string& strParam, Matrix4 m)
{
    GLuint loc = glGetUniformLocation(pShader->GetShader(), strParam.c_str());
    if (loc == -1)
    {
        Log("Param: " + strParam + " does not exist in shader");
        return;
    }

    glUniformMatrix4fv(loc, 1, false, m);
}

void GraphicsDevice::SetUinformFloat(Shader* pShader, FloatParameter* pParam)
{
    GLuint loc = glGetUniformLocation(pShader->GetShader(), pParam->Name.c_str());
    if (loc == -1)
    {
        printf("Float Param: %s does not exist in shader\n", pParam->Name.c_str());
        return;
    }

    switch(pParam->Value.size())
    {
    case 1:
        glUniform1f(loc, pParam->Value[0]);
        break;
    case 2:
        glUniform2f(loc, pParam->Value[0], pParam->Value[1]);
        break;
    case 3:
        glUniform3f(loc, pParam->Value[0], pParam->Value[1], pParam->Value[3]);
        break;
    case 4:
        glUniform4f(loc, pParam->Value[0], pParam->Value[1], pParam->Value[3], pParam->Value[4]);
        break;
    }
}


void GraphicsDevice::Resize(int iWidth, int iHeight)
{
    glViewport( 0, 0, iWidth, iHeight);
}

void GraphicsDevice::Render(Camera* pCamera, RenderObject* pRO)
{
    Material* pMaterial = pRO->GetMaterial();
    Shader* pShader = pMaterial->GetShader();

    glUseProgram(pShader->GetShader());
    HASERROR();

    // Set the camera data
    // SetUniformMatrix(pShader, "ViewMatrix", pCamera->GetViewMatrix());
    Matrix4 mat = pRO->GetTransform()->GetMatrix() * pCamera->GetViewProjection();
    SetUniformMatrix(pShader, "WorldViewProjectionMatrix", mat);

    std::vector<FloatParameter*>& floatParams = pMaterial->GetFloatParams();
    for (unsigned int i = 0; i < floatParams.size(); ++i)
    {
        FloatParameter* pParam = floatParams[i];
        SetUinformFloat(pShader, pParam);
    }

    glBindVertexArray(pRO->GetVertexBuffer()->GetVertexArray());
    HASERROR();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pRO->GetIndexBuffer()->GetBuffer());

    HASERROR();

    glDrawElements(GL_TRIANGLES, pRO->GetElementCount(), GL_UNSIGNED_INT, 0);
    HASERROR();
}

void GraphicsDevice::SetClearColor(float r, float g, float b)
{
    glClearColor(r, g, b, 1.0);
}

void GraphicsDevice::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}