#include "Sound.h"

Sound::Sound()
{
	engine = createIrrKlangDevice();
	active = false;
}


ISoundEngine* Sound::Engine()
{
	return engine;
}