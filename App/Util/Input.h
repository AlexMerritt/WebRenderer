#ifndef __INPUT__
#define __INPUT__

typedef unsigned int Key;

static const int NUM_KEYS = 256;

class Keyboard
{
private:
    struct KeyboardBuffer
    {
        bool Keys[NUM_KEYS];
    };

public:
    Keyboard()
    {
        ZeroBuffer(m_currentBuffer);
        ZeroBuffer(m_lastBuffer);
    }

    void Update()
    {
        CopyBuffer(m_lastBuffer, m_currentBuffer);
        ZeroBuffer(m_currentBuffer);
    }

    void KeyUp(Key key) { m_currentBuffer.Keys[key] = true;}
    void KeyDown(Key key) { m_currentBuffer.Keys[key] = false; }
    
    bool IsKeyDown(Key key) { return m_currentBuffer.Keys[key]; }
    bool KeyPressed(Key key) { return m_currentBuffer.Keys[key] && !m_lastBuffer.Keys[key]; }
    bool KeyReleased(Key key) { return !m_currentBuffer.Keys[key] && m_lastBuffer.Keys[key]; }

private:
    void ZeroBuffer(KeyboardBuffer& buffer)
    {
        for(unsigned int i = 0; i < NUM_KEYS; ++i)
        {
            buffer.Keys[i] = 0;
        }
    }

    void CopyBuffer(KeyboardBuffer& destBuffer, KeyboardBuffer& srcBuffer)
    {
        for(unsigned int i = 0; i < NUM_KEYS; ++i)
        {
            destBuffer.Keys[i] = srcBuffer.Keys[i];
        }
    }

private:
    KeyboardBuffer m_lastBuffer;
    KeyboardBuffer m_currentBuffer;
};

class Mouse
{

};

#endif