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
	void saveScore(int);
	void increaseScore(int, int);
	void resetScore(int);
	void decreaseScore(int, int);
	void setScore(int, int);
	int getScore(int);
};

