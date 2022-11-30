#include "Board.h"
#include <algorithm>
#include <iostream>

Board::Board(std::string filename) {
    cur_block = nullptr;
    next_block = nullptr;
    level = std::make_shared<Level0>(filename);
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
    if (endgame()) {
        std::cout << "end!" << std::endl;
        return;
    }
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
    isBlind = true;
}

void Board::unsetBlind() {
    isBlind = false;
}

bool Board::getBlind(){
    return isBlind;
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

bool Board::left() {
    cur_block->left();
    // if out of index;
    for (int i = 0; i < 4; i++) {
        if (cur_block->getVectorPosn()[cur_block->findIndex()][i].x < 0) {
            cur_block->right();
            return true;
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
            return true;
        }
    }
    //如果有heavy的情况下，trigger down，如果down不下去了就return false，createblock
    for (int i = 0; i < cur_block->getHeavyLevel(); i++) {
        if (this->down() == 2) {
            return false;
        }
    }
    return true;  
}

bool Board::right() {
    cur_block->right();
    for (int i = 0; i < 4; i++) {
        if (cur_block->getVectorPosn()[cur_block->findIndex()][i].x > 10) {
            cur_block->left();
            return true;
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
            return true;
        }
    }
    //如果有heavy的情况下，trigger down，如果down不下去了就return false，createblock
    for (int i = 0; i < cur_block->getHeavyLevel(); i++) {
        if (this->down() == 2) {
            return false;
        }
    }
    return true;
}

void Board::drop() {
    while (down() == 1) {}
    createBlock();
}

int Board::down() {
    cur_block->down();
    //检查有没有out of range
    for (int i = 0; i < 4; i++) {
        if (cur_block->getVectorPosn()[cur_block->findIndex()][i].y > 17) {
            cur_block->up();
            // end current turn
            //createBlock();
            return 0;
        }
    }
    //检查有没有做出一个成功的down
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
            // createBlock();
            return 0;
        }
    }

    //判断更新完curr block底下有没有别的block
    //没必要createblock,createblock是drop的工作
    //特殊情况：如果是有heavy的情况下，down会自动检查curr block底下有没有别的block，如果有自动createblock，然后return false
    
    cur_block->down();
    bool block_under = false;
    for (int i = 0; i < 4; i++) {
        int count = 0;
        for (auto& selectedblock : cells) {
            if (selectedblock->findPos(cur_block->getVectorPosn()[cur_block->findIndex()][i].x, 
                                    cur_block->getVectorPosn()[cur_block->findIndex()][i].y)) {
                count += 1;
            }          
        }
        if (count >= 2) {
            block_under = true;
        }
    }
    cur_block->up();
    if (block_under == true) {
        //如果是有heavy的情况下如果curr block底下有别的block,自动createblock
        if (cur_block->getHeavyLevel() > 0) {
            createBlock();
            //在heavy的情况下如果当底下有block
            return 2;
        }
        //在不是heavy的情况下如果当底下有block
        return 0;
    }
    
    //如果底下没block
    return 1;
}

void Board::rotateCW() {
    cur_block->rotateCW();
    // if out of index
    for (int i = 0; i < 4; i++) {
        if (cur_block->getVectorPosn()[cur_block->findIndex()][i].x > 10) {
            cur_block->rotateAW();
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
            cur_block->rotateAW();
            return;
        }
    }
}

void Board::rotateAW() {
    cur_block->rotateAW();
    for (int i = 0; i < 4; i++) {
        if (cur_block->getVectorPosn()[cur_block->findIndex()][i].x > 10) {
            cur_block->rotateCW();
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

void Board::heavy() {
    cur_block->setHeavyLevel(cur_block->getHeavyLevel() + 2);
}

void Board::force(char type) {
    if (type == 'I') {cur_block = std::make_shared<I_block>();}
    else if (type == 'J') {cur_block = std::make_shared<J_block>();}
    else if (type == 'L') {cur_block = std::make_shared<L_block>();}
    else if (type == 'O') {cur_block = std::make_shared<O_block>();}
    else if (type == 'S') {cur_block = std::make_shared<S_block>();}
    else if (type == 'Z') {cur_block = std::make_shared<Z_block>();}
    else if (type == 'T') {cur_block = std::make_shared<T_block>();}
    cells.pop_back();
    cells.push_back(cur_block);
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

bool Board::endgame() {
    int count = 0;
    for (auto& selectedblock : cells) {
        for (int i = 0; i < 4; i++) {
            if (selectedblock->getVectorPosn()[selectedblock->findIndex()][i].y <= 3) {
                count += 1;
            }          
        }
    }
    if (count > 4) {
        return true;
    }
    return false;
}    

