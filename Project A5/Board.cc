#include "Board.h"



Board::Board() {
    cur_block = nullptr;
    next_block = nullptr;
    level = std::make_shared<Level1>(Level1{});
    score = std::make_shared<Score>(Score{level});
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

bool Board::findPos(int& x, int& y) {
    for (auto& b: cells) {
        if (b->findPos(x, y)) {
            return true;
        }
    }
    return false;
}

void Board::left() {
    cur_block->left();
    for (auto& outer: cur_block->getVectorPosn()[cur_block->findIndex()]) {
        // out of index
        if (outer.x < 0) {
            cur_block->right();
            return;
        }
    }
    // 这里要判断是否有重合的pos 如果有重合就right 下面几个method同理
}

void Board::right() {cur_block->right();}

void Board::drop() {
    cur_block->drop();
    createBlock();
}

void Board::down() {cur_block->down();}

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
                    for (auto& arrayPos: b->getVectorPosn()) {
                        for (auto& pos: arrayPos) {
                            if (pos.y == i && pos.x >= 0 && pos.x <= totalCol) {
                                pos.visible = false;
                            }
                        }
                    }
                }
                // let all upper pos down one
                for (int m = i - 1; m > 3; m--) {
                    for (int n = 0; n <= totalCol; n++) {
                        for (auto& b: cells) {
                            for (auto& arrayPos: b->getVectorPosn()) {
                                for (auto& pos: arrayPos) {
                                    if (pos.y == m && pos.x == n) {
                                        pos.y += 1;
                                    }
                                }
                            }
                        }
                    }
                }
                numRow += 1;      
            }
        }
        i += 1;
    }
    score->cleanRow(numRow);
}
