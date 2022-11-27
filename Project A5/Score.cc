#include "Score.h"

int Score::getScore() {return score;}

int Score::getHscore() {return highestScore;}

int Score::getLevel() {return level->getCurlevel();}

void Score::setLevel(std::shared_ptr<Level> newLevel) {
    level = newLevel;
} 

void Score::cleanRow(int numRow) {
    score += (getLevel() + numRow) * (getLevel() + numRow);
    if (score > highestScore) {
        highestScore = score;
    }
}

void Score::addScore(int num) {score += num;} //说实话我不知道这个function到底是在干嘛 已经有cleanRow了我不知道需不需要这个到底

void Score::restart() {score = 0;}
