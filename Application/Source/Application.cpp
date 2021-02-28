
#include "Application.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>


#include "SceneShop.h"
//#include "SceneMaster.h"
#include "SceneTrivia.h"
#include "SceneSearch.h"
#include "SceneIntro.h"
#include "MainMenu.h"
#include "SceneDrive.h"

GLFWwindow* m_window;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

bool Application::IsKeyPressed(unsigned short key)
{
	return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

Application::Application()
{
}

Application::~Application()
{
}

unsigned Application::m_width;
unsigned Application::m_height;

void resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h); //update opengl the new window size
	Application::m_width = w;
	Application::m_height = h;
	glViewport(0, 0, w, h);
}

bool Application::IsMousePressed(unsigned short key) //0 - Left, 1- Right, 2 - Middle
{
	return glfwGetMouseButton(m_window, key) != 0;
}
void Application::GetCursorPos(double* xpos, double* ypos)
{
	glfwGetCursorPos(m_window, xpos, ypos);
}
int Application::GetWindowWidth()
{
	return m_width;
}
int Application::GetWindowHeight()
{
	return m_height;
}

void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

	//HD screen size
	m_width = 1280;
	m_height = 720;
	m_window = glfwCreateWindow(m_width, m_height, "Test Window", NULL, NULL);
	//Create a window and create its OpenGL context
	/*m_window = glfwCreateWindow(800, 600, "Test Window", NULL, NULL);*/

	//If the window couldn't be created
	if (!m_window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);

	glfwSetWindowSizeCallback(m_window, resize_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}
}

void Application::Run()
{
	int sceneType = START_MENU;
	int passengers = 0;
	int money = 0;
	int speed_level = 0;
	int spawn_level = 0;
	int capacity_level = 0;

	Scene* scene_ptr = new MainMenu();
	scene_ptr->Init();

	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !(IsKeyPressed(VK_ESCAPE) && IsKeyPressed(VK_SHIFT)))
	{ // stop removing this feature
		if (scene_ptr->nextScene)
		{
			if (sceneType == SHOP)
			{ //Only takes level ups from shop
				money = scene_ptr->money;
				speed_level = scene_ptr->speed_level;
				spawn_level = scene_ptr->spawn_level;
				capacity_level = scene_ptr->capacity_level;
			}
			else
			{ //Only takes increased passengers & money from games
				passengers += scene_ptr->passengers;
				money += scene_ptr->money;
			}

			scene_ptr->Exit();
			delete scene_ptr;

			if (sceneType + 1 != NUM_SCENES)
				sceneType++;
			else
				sceneType = INTRO;

			if (sceneType == START_MENU) scene_ptr = new MainMenu();
			if (sceneType == INTRO) scene_ptr = new SceneIntro();
			if (sceneType == DRIVE)
			{
				scene_ptr = new SceneDrive();
				scene_ptr->speed_level = speed_level;
				scene_ptr->spawn_level = spawn_level;
				scene_ptr->capacity_level = capacity_level;
			}
			if (sceneType == TRIVIA) scene_ptr = new SceneTrivia();
			if (sceneType == SEARCH) scene_ptr = new SceneSearch();
			if (sceneType == SHOP)
			{ //end of day
				int passenger_ticket = 50; //price of tickets
				scene_ptr = new SceneShop();
				money += passengers * passenger_ticket;
				scene_ptr->money = money;
				scene_ptr->speed_level = speed_level;
				scene_ptr->spawn_level = spawn_level;
				scene_ptr->capacity_level = capacity_level;
			}


			scene_ptr->Init();
		}
		/*if (Application::changeScene)
		{
			switch (scene)
			{
			case Application::S_MAIN:
				scene_ptr = new MainMenu;
				break;
			case Application::S_INTRO:
				scene_ptr = new SceneIntro;
				break;
			case Application::S_DRIVE:
				scene_ptr = new SceneDrive;
				break;
			case Application::S_TRIVIA:
				scene_ptr = new SceneTrivia;
				break;
			case Application::S_SEARCH:
				scene_ptr = new SceneSearch;
				break;
			case Application::S_SHOP:
				scene_ptr = new MainMenu;
				break;
			default:
				break;
			}
		}*/
		scene_ptr->Update(m_timer.getElapsedTime());
		scene_ptr->Render();
		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
		m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

	} //Check if the ESC key had been pressed or if the window had been closed

	scene_ptr->Exit();
	delete scene_ptr;
}

void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}

//check