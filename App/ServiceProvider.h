#ifndef __SERVICE_PROVIDER__
#define __SERVICE_PROVIDER__

#include <string>
#include <map>

class MainSystem
{
public:
    virtual void Initialize() = 0;

    void PrintName()
    {
        printf("System - %s\n", m_strSystemName.c_str());
    }

private:
    std::string m_strSystemName;

    friend class Systems;
};

class Systems
{
public:
    template <typename T>
    static void Register(MainSystem* pSystem){
        
        std::string strTypeName = typeid(T).name();
        pSystem->m_strSystemName = strTypeName;

        pSystem->Initialize();

        s_systems[strTypeName] = pSystem;
    }


    template <typename T>
    static T* Get()
    {
        T* pResult = 0;

        std::string strTypeName = typeid(T).name();

        if(s_systems.find(strTypeName) != s_systems.end())
        {
            pResult = (T*)s_systems[strTypeName];
        }

        return pResult;
    }
    
protected:
    static std::map<std::string, MainSystem*> s_systems;

};

#endif