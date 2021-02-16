#include "Sound.h"

Sound::Sound()
{
	engine = createIrrKlangDevice();
}