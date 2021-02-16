#pragma once
#include "Money.h"

class Score
{
private:
	int score[10];

public:
	Score();

	Money money;
	void saveScore();
};

