#pragma once
#include <irrKlang.h>
#include <iostream>
#include <conio.h>

using namespace irrklang;

#pragma comment(lib, "irrKlang.lib")

class Sound
{
public:
	ISoundEngine* engine;
	Sound();
};
