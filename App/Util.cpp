#include "Util.h"

#include <emscripten/emscripten.h>

void Log(std::string strText)
{
    std::string strMessage = "console.log('" + strText + "')";
    emscripten_run_script(strMessage.c_str());
}
