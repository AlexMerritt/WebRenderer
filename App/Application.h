#ifndef __APPLICATION__
#define __APPLICATION__

#include <string>

class Application{
public:
    Application();

    void Initialize();
    void Frame();

protected:
    void Update();
    void Render();

protected:
    std::string m_strAppName;
};

#endif