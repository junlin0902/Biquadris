#ifndef _BOARDCONTROL_H_
#define _BOARDCONTROL_H_
#include "Board.h"
#include <memory>
#include "View.h"

class BoardControl {
    std::shared_ptr<Board> Board1;
    std::shared_ptr<Board> Board2;
    int round = 1;
    //View view;
    //bool graphic;

    public:
    BoardControl(std::shared_ptr<Board> Board1, std::shared_ptr<Board> Board2/*, bool g*/)
    : Board1{Board1}, Board2{Board2}/*, view{View(g)}, graphic{g} */{
        Board1->createBlock();
        Board2->createBlock();
    }
    void restart();
    void rotateCW(int times);
    void rotateAW(int times);
    void left(int times);
    void right(int times);
    void drop();
    void down(int times);
    void levelup(int num);
    void leveldown(int num);
    void switchRandom();
    std::shared_ptr<Board> getBoard1();
    std::shared_ptr<Board> getBoard2();
    void changeRound();
    void textDisplay();
    void graphDisplay();
    void applyBlind();
    void removeBlind();
};

#endif
