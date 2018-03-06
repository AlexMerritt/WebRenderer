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

    Log("Graphics Device Initialized");
}

void GraphicsDevice::Clear()
{
    glClearColor(0.1, 0.2, 0.4, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}