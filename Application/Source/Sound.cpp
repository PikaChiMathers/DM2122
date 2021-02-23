#include "Sound.h"

Sound::Sound()
{
	engine = createIrrKlangDevice();
}

Sound::~Sound()
{
}


ISoundEngine* Sound::Engine()
{
	return engine;
}