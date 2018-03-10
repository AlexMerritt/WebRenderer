#include "Input.h"

static Keyboard* s_Keyboard = 0;

Keyboard* Keyboard::Get()
{
    return s_Keyboard;
}
void Keyboard::Set(Keyboard* pKeyboard)
{
    s_Keyboard = pKeyboard;
}


Keyboard::Keyboard()
{
    ZeroBuffer(m_currentBuffer);
    ZeroBuffer(m_lastBuffer);
}

void Keyboard::Update()
{
    CopyBuffer(m_lastBuffer, m_currentBuffer);
    ZeroBuffer(m_currentBuffer);
}

void Keyboard::KeyUp(Key key)
{
    m_currentBuffer.Keys[key] = false;
}

void Keyboard::KeyDown(Key key)
{ 
    m_currentBuffer.Keys[key] = true;
}

bool Keyboard::IsKeyDown(Key key) 
{ 
    return m_currentBuffer.Keys[key]; 
}

bool Keyboard::KeyPressed(Key key) 
{
    return m_currentBuffer.Keys[key] && !m_lastBuffer.Keys[key]; 
}

bool Keyboard::KeyReleased(Key key) 
{
    return !m_currentBuffer.Keys[key] && m_lastBuffer.Keys[key]; 
}

void Keyboard::ZeroBuffer(KeyboardBuffer& buffer)
{
    for(unsigned int i = 0; i < NUM_KEYS; ++i)
    {
        buffer.Keys[i] = 0;
    }
}

void Keyboard::CopyBuffer(KeyboardBuffer& destBuffer, KeyboardBuffer& srcBuffer)
{
    for(unsigned int i = 0; i < NUM_KEYS; ++i)
    {
        destBuffer.Keys[i] = srcBuffer.Keys[i];
    }
}
