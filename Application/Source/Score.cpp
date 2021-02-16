#include "Score.h"

Score::Score() : 
	score{ }
{
	passengerCount = 0;
}

void Score::saveScore()
{
	money.SuccessfulTourist(passengerCount);

	int tempscore = money.getMoney();
	for (int i = 9; i > -1; i--) {
		if (tempscore < score[i]) {
			int tempscore2 = score[i];
			score[i] = tempscore;
			tempscore = tempscore2;
		}
	}
}

int Score::getScore(int num)
{
	return score[num];
}
