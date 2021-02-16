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
	void increaseScore(int, int);
	void resetScore(int);
	void decreaseScore(int, int);
	int getScore(int);
};
