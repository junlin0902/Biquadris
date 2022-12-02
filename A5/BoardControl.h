#ifndef _BOARDCONTROL_H_
#define _BOARDCONTROL_H_
#include "View.h"
#include "Board.h"
#include <memory>


class BoardControl {
    std::shared_ptr<Board> Board1;
    std::shared_ptr<Board> Board2;
    int round = 1;
    std::shared_ptr<View> view;
    bool graphic;
    //int seed = 0;

    public:
    BoardControl(std::shared_ptr<Board> Board1, std::shared_ptr<Board> Board2, bool g = false)
    : Board1{Board1}, Board2{Board2}, view{std::make_shared<View>(g)}, graphic{g} {
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
    void heavy();
    void force(char block);
    void levelup(int num);
    void leveldown(int num);
    void norandom();
    void random();
    std::shared_ptr<Board> getBoard1();
    std::shared_ptr<Board> getBoard2();
    void changeRound();
    void display();
    void applyBlind();
    void removeBlind();
    void needGraph();
    //void setSeed(int num);
    void endgame();

    // when cur is in its initial pos
    // this is try to find if this block can move its
    // first step when it has heavy != 0
    // can move return 1 otherwise 0
    bool if_firststep();
};

#endif
