#ifndef _SCORE_H_
#define _SCORE_H_
#include "Level.h"

class Score {
    int score;
    int highestScore;
    Level* level;

    public:
    // return score in class Score
    int getScore();

    // return hignestScore in class Score
    int getHscore();
    int getLevel();

    void setScore(int newScore);
    void setHscore(int newHscore);

    void addScore();
    void restart();
};

#endif
