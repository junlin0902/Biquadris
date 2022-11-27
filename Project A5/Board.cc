#include "Board.h"

Board::Board() {
    cur_block = nullptr;
    next_block = nullptr;
    level = nullptr;
    score = nullptr;
}

void Board::setCurBlock(std::shared_ptr<Block> block) {cur_block = block;}
void Board::setNextBlock(std::shared_ptr<Block> block) {next_block = block;}
void Board::setLevel(int l) {level = l;}
void Board::setScore(int s) {score = s;}

std::shared_ptr<Block> Board::getCurBlock() {return cur_block;}
std::shared_ptr<Block> Board::getNextBlock() {return next_block;}
std::shared_ptr<Level> Board::getLevel() {return level;}
std::shared_ptr<Score> Board::getScore() {return score;}

int Board::totalBlock() {return num_block;}

std::shared_ptr<Block> Board::createBlock() {
    return getLevel()->createBlock();
}


