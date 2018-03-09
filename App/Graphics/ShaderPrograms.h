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
    "void main(void)                                         \n"
    "{                                                       \n"
    "    gl_Position = ViewMatrix * inputPosition;           \n"
    "    gl_Position = ProjectionMatrix * gl_Position;       \n"
    "}";

char fShaderStr[] =
    "#version 300 es                              \n"
    "precision mediump float;                     \n"
    "out vec4 fragColor;                          \n"
    "void main()                                  \n"
    "{                                            \n"
    "   fragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );  \n"
    "}                                            \n";

