#pragma once

#include "Maps.h"
#include "Application.h"

class MiniGames
{
public:
	enum class MG_TYPE
	{
		MG_TRIVIA,
		NUM_MG,
	};

	MiniGames();
	~MiniGames();

	virtual void Update(double dt) = 0;

	void Start_MG(MG_TYPE type);

	bool isRunning();

private:
	MG_TYPE type;
	Maps map;
	bool is_running, game_started;
};

