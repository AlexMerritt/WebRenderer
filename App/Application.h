#ifndef _APPLICATION_
#define _APPLICATION_

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