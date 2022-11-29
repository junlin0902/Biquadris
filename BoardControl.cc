#include "BoardControl.h"
#include "Board.h"
#include <iostream>

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
            Board1->left();
        }
        return;
    }
    for (int i = 0; i < times; i++) {
            Board2->left();
    }
}

void BoardControl::right(int times) {
    if (round == 1) {
        for (int i = 0; i < times; i++) {
            Board1->right();
        }
        return;
    }
    for (int i = 0; i < times; i++) {
            Board2->right();
    }
}

void BoardControl::drop() {
    if (round == 1) {
        Board1->drop();
        round = 2;
        return;
    }
    Board2->drop();
    round = 1;
}

void BoardControl::down(int times) {
    if (round == 1) {
        for (int i = 0; i < times; i++) {
            //如果没catch说明更新完curr block底下没有别的block
            //如果catch说明当前循环下更新完curr block底下有别的block，
            // 直接change round，return终止循环
            try {
                Board1->down();
            } catch (bool block_under) {
                this->changeRound();
                return;
            }
        }
        return;
    }
    for (int i = 0; i < times; i++) {
        //如果没catch说明更新完curr block底下没有别的block
        //如果catch说明当前循环下更新完curr block底下有别的block，
        // 直接change round，return终止循环        
        try {
            Board2->down();
        } catch (bool block_under) {
            this->changeRound();
            return;
        }
    }
}

void BoardControl::levelup(int num) {
    if (round == 1) {
        int curLevel = Board1->getLevel()->getCurlevel();
        if (curLevel + num == 0) {
            Board1->setLevel(std::make_shared<Level1>());
        } else if (curLevel + num == 1) {
            Board1->setLevel(std::make_shared<Level1>());
        } else if (curLevel + num == 2) {
            Board1->setLevel(std::make_shared<Level1>());
        } else if (curLevel + num == 3) {
            Board1->setLevel(std::make_shared<Level1>());
        } else if (curLevel + num == 4) {
            Board1->setLevel(std::make_shared<Level1>());
        } else {
            std::cout << "invalid level" << std::endl;
        }
    }
    int curLevel = Board2->getLevel()->getCurlevel();
    if (curLevel + num == 0) {
        Board2->setLevel(std::make_shared<Level1>());
    } else if (curLevel + num == 1) {
        Board2->setLevel(std::make_shared<Level1>());
    } else if (curLevel + num == 2) {
        Board2->setLevel(std::make_shared<Level1>());
    } else if (curLevel + num == 3) {
        Board2->setLevel(std::make_shared<Level1>());
    } else if (curLevel + num == 4) {
        Board2->setLevel(std::make_shared<Level1>());
    } else {
        std::cout << "invalid level" << std::endl;
    }
}

void BoardControl::leveldown(int num) {
    if (round == 1) {
        int curLevel = Board1->getLevel()->getCurlevel();
        if (curLevel - num == 0) {
            Board1->setLevel(std::make_shared<Level1>());
        } else if (curLevel - num == 1) {
            Board1->setLevel(std::make_shared<Level1>());
        } else if (curLevel - num == 2) {
            Board1->setLevel(std::make_shared<Level1>());
        } else if (curLevel - num == 3) {
            Board1->setLevel(std::make_shared<Level1>());
        } else if (curLevel - num == 4) {
            Board1->setLevel(std::make_shared<Level1>());
        } else {
            std::cout << "invalid level" << std::endl;
        }
    }
    int curLevel = Board2->getLevel()->getCurlevel();
    if (curLevel - num == 0) {
        Board2->setLevel(std::make_shared<Level1>());
    } else if (curLevel - num == 1) {
        Board2->setLevel(std::make_shared<Level1>());
    } else if (curLevel - num == 2) {
        Board2->setLevel(std::make_shared<Level1>());
    } else if (curLevel - num == 3) {
        Board2->setLevel(std::make_shared<Level1>());
    } else if (curLevel - num == 4) {
        Board2->setLevel(std::make_shared<Level1>());
    } else {
        std::cout << "invalid level" << std::endl;
    }
}

void BoardControl::switchRandom() {
    if (round == 1) {
        Board1->getLevel()->changeRandom();
        return;
    }
    Board2->getLevel()->changeRandom();
}


std::shared_ptr<Board> BoardControl::getBoard1() {return Board1;}

std::shared_ptr<Board> BoardControl::getBoard2() {return Board2;}

void BoardControl::changeRound() {
    if (round == 1) {
        round = 2;
        return;
    }
    round = 1;
}
