#include "Board.h"



Board::Board() {
    cur_block = nullptr;
    next_block = nullptr;
    level = nullptr;
    score = nullptr;
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

std::shared_ptr<Block> Board::createBlock() {
    return getLevel()->createBlock();
}

bool Board::findPos(int& x, int& y) {
    for (auto& b: cells) {
        if (b->findPos(x, y)) {
            return true;
        }
    }
    return false;
}


void Board::cleanRow() {
    for (int i = totalRow; i > 3; i--) {
        for (int j = 0; j <= totalCol; j++) {
            if (findPos(j, i) == false) {
                break;
            }
            if (j == totalCol && findPos(j, i)) {
                // clean row

            }
        }
    }
}
