#pragma once
#include "Money.h"

class Score
{
private:
	int score[10];
	int passengerCount;

public:
	Score();

	Money money;
	void saveScore();
	int getScore(int);
};

