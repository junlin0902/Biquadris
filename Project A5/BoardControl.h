#ifndef _BOARDCONTROL_H_
#define _BOARDCONTROL_H_
#include "Board.h"

class BoardControl {
    Board* Board1;
    Board* Board2;
    int turns = 1;

    public:
    BoardControl(Board* Board1, Board* Board2): Board1{Board1}, Board2{Board2} {}
    void restart();
    void endGame();
    void rotateCW(int times);
    void rotateAW(int times);
    void left(int times);
    void right(int times);
    void drop();
    void levelup(int num);
    void leveldown(int num);
};

#ifndef
