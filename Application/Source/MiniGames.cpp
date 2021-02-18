#include "MiniGames.h"

MiniGames::MiniGames()
{
	is_running = false;
}

MiniGames::~MiniGames()
{
}

void MiniGames::Start_MG(MG_TYPE type)
{
	is_running = true; //MiniGame will only run 
	game_started = false; //Game only starts after player clicks start
	this->type = type;
}

bool MiniGames::isRunning()
{
	return is_running;
}
