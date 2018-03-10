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
    Keyboard();

    void Update();

    void KeyUp(Key key);
    void KeyDown(Key key);
    
    bool IsKeyDown(Key key);
    bool KeyPressed(Key key);
    bool KeyReleased(Key key);

    static Keyboard* Get();
    static void Set(Keyboard* pKeyboard);

private:
    void ZeroBuffer(KeyboardBuffer& buffer);
    void CopyBuffer(KeyboardBuffer& destBuffer, KeyboardBuffer& srcBuffer);

private:
    KeyboardBuffer m_lastBuffer;
    KeyboardBuffer m_currentBuffer;   
};

class Mouse
{
public:
    Mouse();

    static Mouse* Get();
    static void Set(Mouse* pMouse);
};

#endif