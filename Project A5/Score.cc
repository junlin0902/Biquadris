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

void Score::addScore(int num) {score += num;}

void Score::restart() {score = 0;}
