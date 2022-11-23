#include "Score.h"

int Score::getScore() {return score;}

int Score::getHscore() {return highestScore;}

int Score::getLevel() {return level->getCurlevel();}

void Score::setScore(int newScore) {score = newScore;}

void Score::setHscore(int newHscore) {highestScore = newHscore;}
