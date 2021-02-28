#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"

class Application
{
public:
    enum SCENE_TYPE
    {
        START_MENU = 0,
        INTRO,
        DRIVE,
        TRIVIA,
        SEARCH,
        SHOP,
        NUM_SCENES,
    };

    Application();
    ~Application();
    void Init();
    void Run();
    void Exit();
    static bool IsKeyPressed(unsigned short key);

    static bool IsMousePressed(unsigned short key);
    static void GetCursorPos(double* xpos, double* ypos);
    static int GetWindowWidth();
    static int GetWindowHeight();
    static unsigned m_width;
    static unsigned m_height;


private:

    //Declare a window object
    StopWatch m_timer;
};

#endif