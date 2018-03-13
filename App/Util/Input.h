#ifndef __INPUT__
#define __INPUT__

typedef unsigned int Key;

namespace KeyCode 
{
    static const Key _0 = 48;
    static const Key _1 = 49;
    static const Key _2 = 50;
    static const Key _3 = 51;
    static const Key _4 = 52;
    static const Key _5 = 53;
    static const Key _6 = 54;
    static const Key _7 = 55;
    static const Key _8 = 56;
    static const Key _9 = 57;
    static const Key A = 65;
    static const Key B = 66;
    static const Key C = 67;
    static const Key D = 68;
    static const Key E = 69;
    static const Key F = 70;
    static const Key G = 71;
    static const Key H = 72;
    static const Key I = 73;
    static const Key J = 74;
    static const Key K = 75;
    static const Key L = 76;
    static const Key M = 77;
    static const Key N = 78;
    static const Key O = 79;
    static const Key P = 80;
    static const Key Q = 81;
    static const Key R = 82;
    static const Key S = 83;
    static const Key T = 84;
    static const Key U = 85;
    static const Key V = 86;
    static const Key W = 87;
    static const Key X = 88;
    static const Key Y = 89;
    static const Key Z = 90;
};


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