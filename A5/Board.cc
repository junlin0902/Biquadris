#include "Board.h"
#include <algorithm>
#include <iostream>

Board::Board() {
    cur_block = nullptr;
    next_block = nullptr;
    level = std::make_shared<Level1>();
    score = std::make_shared<Score>(level);
}


void Board::setCurBlock(std::shared_ptr<Block> block) {cur_block = block;}
void Board::setNextBlock(std::shared_ptr<Block> block) {next_block = block;}
void Board::setLevel(std::shared_ptr<Level> l) {level = l;}
void Board::setScore(std::shared_ptr<Score> s) {score = s;}

std::shared_ptr<Block> Board::getCurBlock() {return cur_block;}
std::shared_ptr<Block> Board::getNextBlock() {return next_block;}
std::shared_ptr<Level> Board::getLevel() {return level;}
std::shared_ptr<Score> Board::getScore() {return score;}

int Board::totalBlock() {return num_block;}

void Board::createBlock() {
    if (cur_block == nullptr) {
        cur_block = level->createBlock();
        cells.push_back(cur_block);
        next_block = level->createBlock();
        return;
    } 
    cur_block = next_block;
    next_block = level->createBlock();
    cells.push_back(cur_block);
}

void Board::setBlind() {
    this->isBlind = true;
}

void Board::unsetBlind() {
    this->isBlind = false;
}

bool Board::getBlind(){
    return this->isBlind;
}

bool Board::findPos(int& x, int& y) {
    for (auto& b: cells) {
        if (b->findPos(x, y)) {
            return true;
        }
    }
    return false;
}

char Board::findType(int& x, int& y) {
    for (auto& b: cells) {
        if (b->findPos(x, y)) {
            return b->blockType();
        }
    }
    return ' ';
}

void Board::left() {
    cur_block->left();
    // if out of index;
    for (int i = 0; i < 4; i++) {
        if (cur_block->getVectorPosn()[cur_block->findIndex()][i].x < 0) {
            cur_block->right();
            return;
        }
    }

    // 这里要判断是否有重合的pos 如果有重合就right 下面几个method同理
    //traverse every block stored in cells
    //把cur_block里的每一个posn去和存的cell里的一个block里curr_state的4个posn去做比较(std::count)
    for (int i = 0; i < 4; i++) {
        int count = 0;
        for (auto& selectedblock : cells) {
            if (selectedblock->findPos(cur_block->getVectorPosn()[cur_block->findIndex()][i].x, 
                                       cur_block->getVectorPosn()[cur_block->findIndex()][i].y)) {
                count += 1;
            }          
        }
        if (count >= 2) {
            cur_block->right();
            return;
        }
    }
}

void Board::right() {
    cur_block->right();
    for (int i = 0; i < 4; i++) {
        if (cur_block->getVectorPosn()[cur_block->findIndex()][i].x > 10) {
            cur_block->left();
            return;
        }
    }
    for (int i = 0; i < 4; i++) {
        int count = 0;
        for (auto& selectedblock : cells) {
            if (selectedblock->findPos(cur_block->getVectorPosn()[cur_block->findIndex()][i].x, 
                                       cur_block->getVectorPosn()[cur_block->findIndex()][i].y)) {
                count += 1;
            }          
        }
        if (count >= 2) {
            cur_block->left();
            return;
        }
    }
}

void Board::drop() {
    cur_block->drop();
    while (true) {
        for (int i = 0; i < 4; i++) {
            int count = 0;
            for (auto& selectedblock: cells) {
                if (selectedblock->findPos(cur_block->getVectorPosn()[cur_block->findIndex()][i].x, 
                                       cur_block->getVectorPosn()[cur_block->findIndex()][i].y)) {
                count += 1;
                }   
            }
            if (count >= 2) {
                cur_block->up();
                break;
            }
            if (i == 3) {
                createBlock();
                return;
            }
        }
    }
}

void Board::down() {
    cur_block->down();
    for (int i = 0; i < 4; i++) {
        if (cur_block->getVectorPosn()[cur_block->findIndex()][i].y > 17) {
            cur_block->up();
            // end current turn
            createBlock();
            return;
        }
    }
    for (int i = 0; i < 4; i++) {
        int count = 0;
        for (auto& selectedblock : cells) {
            if (selectedblock->findPos(cur_block->getVectorPosn()[cur_block->findIndex()][i].x, 
                                       cur_block->getVectorPosn()[cur_block->findIndex()][i].y)) {
                count += 1;
            }          
        }
        if (count >= 2) {
            cur_block->up();
            createBlock();
            return;
        }
    }
}

void Board::rotateCW() {
    cur_block->rotateCW();
    for (int i = 0; i < 4; i++) {
        int count = 0;
        for (auto& selectedblock : cells) {
            if (selectedblock->findPos(cur_block->getVectorPosn()[cur_block->findIndex()][i].x, 
                                       cur_block->getVectorPosn()[cur_block->findIndex()][i].y)) {
                count += 1;
            }          
        }
        if (count >= 2) {
            cur_block->rotateAW();
            return;
        }
    }
}

void Board::rotateAW() {
    cur_block->rotateAW();
    for (int i = 0; i < 4; i++) {
        int count = 0;
        for (auto& selectedblock : cells) {
            if (selectedblock->findPos(cur_block->getVectorPosn()[cur_block->findIndex()][i].x, 
                                       cur_block->getVectorPosn()[cur_block->findIndex()][i].y)) {
                count += 1;
            }          
        }
        if (count >= 2) {
            cur_block->rotateCW();
            return;
        }
    }
}

void Board::cleanRow() {
    int numRow = 0;
    for (int i = totalRow; i > 3; i--) {
        for (int j = 0; j <= totalCol; j++) {
            if (findPos(j, i) == false) {
                break;
            }
            if (j == totalCol && findPos(j, i)) {
                // clean row
                // let all pos in current row to be invisible
                for (auto& b: cells) {
                    for (int m = 0; m <= totalCol; m++) {
                        if (b->findPos(m, i)) {
                            b->changeVis(m, i);
                        }
                    }
                }
                // let all upper pos down one
                for (int m = i - 1; m > 3; m--) {
                    for (int n = 0; n <= totalCol; n++) {
                        for (auto& b: cells) {
                            if (b->findPos(n, m)) {
                                b->changeY(n, m, 1);
                            }
                        }
                    }
                }
                numRow += 1;
                i += 1;
            }
        }
    }
    score->cleanRow(numRow);
}


void Board::changeBlind() {
    if (isBlind) {
        isBlind = false;
    }
    isBlind = true;
}

void Board::heavy() {
    cur_block->setHeavyLevel(2);
}

void Board::force(std::shared_ptr<Block> force) {
    *cur_block = *force;
}

void Board::reset() {
    int size = cells.size();
    for (int i = 0; i < size; i++) {
        cells.pop_back();
    }
    cur_block = level->createBlock();
    cells.push_back(cur_block);
    next_block = level->createBlock();
    score->restart();
}
