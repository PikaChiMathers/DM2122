#pragma once
#include <irrKlang.h>
#include <iostream>
#include <conio.h>

using namespace irrklang;

#pragma comment(lib, "irrKlang.lib")

class Sound
{
private:
	ISoundEngine* engine;
	bool active;

public:
	Sound();
	~Sound();
	ISoundEngine* Engine();
};
