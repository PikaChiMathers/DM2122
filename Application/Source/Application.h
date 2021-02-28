
#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"

class Application
{
public:
	enum ENUM_SCENE
	{
		S_MAIN,
		S_INTRO,
		S_DRIVE,
		S_TRIVIA,
		S_CHASE,
		S_SHOP
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
	static void changeScene(ENUM_SCENE scene);
	static unsigned m_width;
	static unsigned m_height;

	//static void changeScene(int scene);


	static ENUM_SCENE scene;

private:

	//Declare a window object
	StopWatch m_timer;
};

#endif