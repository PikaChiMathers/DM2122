#include "Score.h"

Score::Score() : 
	score{ }
{

}

void Score::saveScore()
{
	int tempscore = money.getMoney();
	for (int i = 9; i > -1; i--) {
		if (tempscore < score[i]) {
			int tempscore2 = score[i];
			score[i] = tempscore;
			tempscore = tempscore2;
		}
	}
}
