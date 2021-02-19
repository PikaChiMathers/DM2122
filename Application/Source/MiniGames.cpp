#include "MiniGames.h"

MiniGames::MiniGames()
{
	is_running = false; //boolean for if a MiniGame is running
	game_started = false; //Game only starts after player clicks start
}

MiniGames::~MiniGames()
{
}

void MiniGames::Start_MG(MG_TYPE type)
{
	is_running = true;
	this->type = type;
}

bool MiniGames::isRunning()
{
	return is_running;
}
