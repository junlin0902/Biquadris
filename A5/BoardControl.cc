#include "BoardControl.h"
#include "Board.h"
#include <iostream>
#include "View.h"

void BoardControl::restart() {
    Board1->reset();
    Board2->reset();
}


void BoardControl::rotateCW(int times) {
    if (round == 1) {
        for (int i = 0; i < times; i++) {
            Board1->rotateCW();
        }
        return;
    }
    for (int i = 0; i < times; i++) {
        Board2->rotateCW();
    }
}

void BoardControl::rotateAW(int times) {
    if (round == 1) {
        for (int i = 0; i < times; i++) {
            Board1->rotateAW();
        }
        return;
    }
    for (int i = 0; i < times; i++) {
            Board2->rotateAW();
    }
}

void BoardControl::left(int times) {
    if (round == 1) {
        for (int i = 0; i < times; i++) {
            //只有是heavy的情况下board::right可能会return false
            if (Board1->left() == false) {
                changeRound();
                return;
            } 
        }
        return;
    }
    for (int i = 0; i < times; i++) {
            //只有是heavy的情况下board::right可能会return false
            if (Board2->left() == false) {
                changeRound();
                return;
            } 
    }
}

void BoardControl::right(int times) {
    if (round == 1) {
        for (int i = 0; i < times; i++) {
            //只有是heavy的情况下board::right可能会return false
            if (Board1->right() == false) {
                changeRound();
                return;
            }  
        }
        return;
    }
    for (int i = 0; i < times; i++) {
        if (Board2->right() == false) {
            changeRound();
            return;
        }  
    }
}

void BoardControl::drop() {
    if (round == 1) {
        Board1->drop();
        changeRound();
        return;
    }
    Board2->drop();
    changeRound();
}

void BoardControl::down(int times) {
    if (round == 1) {
        for (int i = 0; i < times; i++) {
            if ((Board1->down() == 2)) {
                changeRound();
                return;
            }
        }
        return;
    }
    for (int i = 0; i < times; i++) {
        if ((Board2->down() == 2)) {
            changeRound();
            return;
        }
    }
}

void BoardControl::heavy() {
    if (round == 1) {
        Board2->heavy();
        return;
    }
    Board1->heavy(); 
}

void BoardControl::force(char block) {
    if (round == 1) {
        Board2->force(block);
        return;
    }
    Board1->force(block);
}

void BoardControl::levelup(int num) {
    if (round == 1) {
        int curLevel = Board1->getLevel()->getCurlevel();
        if (curLevel + num == 1) {
            Board1->setLevel(std::make_shared<Level1>());
        } else if (curLevel + num == 2) {
            Board1->setLevel(std::make_shared<Level2>());
        } else if (curLevel + num == 3) {
            Board1->setLevel(std::make_shared<Level3>("sequence1.txt"));
            Board1->getCurBlock()->setHeavyLevel(Board1->getCurBlock()->getHeavyLevel() + 2);
            Board1->getNextBlock()->setHeavyLevel(Board1->getNextBlock()->getHeavyLevel() + 2);
        } else if (curLevel + num >= 4) {
            Board1->setLevel(std::make_shared<Level4>("sequence1.txt"));
            Board1->getCurBlock()->setHeavyLevel(Board1->getCurBlock()->getHeavyLevel() + 2);
            Board1->getNextBlock()->setHeavyLevel(Board1->getNextBlock()->getHeavyLevel() + 2);
        }
        Board1->getScore()->setLevel(Board1->getLevel());
        return;
    }
    int curLevel = Board2->getLevel()->getCurlevel();
    if (curLevel + num == 1) {
        Board2->setLevel(std::make_shared<Level1>());
    } else if (curLevel + num == 2) {
        Board2->setLevel(std::make_shared<Level2>());
    } else if (curLevel + num == 3) {
        Board2->setLevel(std::make_shared<Level3>("sequence2.txt"));
        Board2->getCurBlock()->setHeavyLevel(Board2->getCurBlock()->getHeavyLevel() + 2);
        Board2->getNextBlock()->setHeavyLevel(Board2->getNextBlock()->getHeavyLevel() + 2);
    } else if (curLevel + num >= 4) {
        Board2->setLevel(std::make_shared<Level4>("sequence2.txt"));
        Board2->getCurBlock()->setHeavyLevel(Board2->getCurBlock()->getHeavyLevel() + 2);
        Board2->getNextBlock()->setHeavyLevel(Board2->getNextBlock()->getHeavyLevel() + 2);
    }
    Board2->getScore()->setLevel(Board2->getLevel());
}

void BoardControl::leveldown(int num) {
    if (round == 1) {
        int curLevel = Board1->getLevel()->getCurlevel();
        if (curLevel - num <= 0) {
            Board1->setLevel(std::make_shared<Level0>("sequence1.txt"));
        } else if (curLevel - num == 1) {
            Board1->setLevel(std::make_shared<Level1>());
        } else if (curLevel - num == 2) {
            Board1->setLevel(std::make_shared<Level2>());
        } else if (curLevel - num == 3) {
            Board1->setLevel(std::make_shared<Level3>("sequence1.txt"));
        }
        Board1->getScore()->setLevel(Board1->getLevel());
        return;
    }
    int curLevel = Board2->getLevel()->getCurlevel();
    if (curLevel - num <= 0) {
        Board2->setLevel(std::make_shared<Level0>("sequence2.txt"));
    } else if (curLevel - num == 1) {
        Board2->setLevel(std::make_shared<Level1>());
    } else if (curLevel - num == 2) {
        Board2->setLevel(std::make_shared<Level2>());
    } else if (curLevel - num == 3) {
        Board2->setLevel(std::make_shared<Level3>("sequence2.txt"));
    }
    Board2->getScore()->setLevel(Board2->getLevel());
}

void BoardControl::switchRandom() {
    if (round == 1) {
        Board1->getLevel()->changeRandom();
        return;
    }
    Board2->getLevel()->changeRandom();
}

int BoardControl::find_whowin() {return whowin;}

std::shared_ptr<Board> BoardControl::getBoard1() {return Board1;}

std::shared_ptr<Board> BoardControl::getBoard2() {return Board2;}

void BoardControl::changeRound() {
    if (round == 1) {
        Board1->cleanRow();
        round = 2;
        return;
    }
    Board2->cleanRow();
    round = 1;
}

/*void BoardControl::textDisplay() {
    view.displayText(Board1, Board2);
}

void BoardControl::graphDisplay() {
    view.displayGraph(Board1, Board2);
}

void BoardControl::applyBlind() {
    if (round == 1){
        Board2->setBlind();
    }
    else {
        Board1->setBlind();
    } 
}

void BoardControl::removeBlind() {
    if (round == 1) {
        Board2->unsetBlind();
    }
    else {
        Board1->unsetBlind();
    }    
}*/
