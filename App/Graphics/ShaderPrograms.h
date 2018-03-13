#ifndef __SHADER_PROGRAM__
#define __SHADER_PROGRAM__

char vShaderStr[] =
      "#version 300 es                          \n"
      "layout(location = 0) in vec4 vPosition;  \n"
      "void main()                              \n"
      "{                                        \n"
      "   gl_Position = vPosition;              \n"
      "}                                        \n";
      
char vs[] =
    "#version 300 es                                         \n"
    "layout(location = 0) in vec4 inputPosition;             \n"
    "uniform mat4 ViewMatrix;                                \n"
    "uniform mat4 ProjectionMatrix;                          \n"
    "out vec3 color;                                         \n"
    "void main(void)                                         \n"
    "{                                                       \n"
    "    gl_Position = ViewMatrix * inputPosition;           \n"
    "    gl_Position = ProjectionMatrix * gl_Position;       \n"
    "    color = vec3(0.25, 0.1, 0.65);                      \n"
    "}";

char fShaderStr[] =
    "#version 300 es                              \n"
    "precision mediump float;                     \n"
    "in vec3 color;                               \n"
    "out vec4 fragColor;                          \n"
    "void main()                                  \n"
    "{                                            \n"
    "   fragColor = vec4 ( color, 1.0 );  \n"
    "}                                            \n";


#endif