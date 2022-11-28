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
    //traverse every block stored in cells
    for (auto& selectedblock : cells) {
        int count = 0;

        //把cur_block里的每一个posn去和存的cell里的一个block里curr_state的4个posn去做比较(std::count)
        for (auto& posn : cur_block->getVectorPosn()[cur_block->findIndex()]) {
            count = std::count(selectedblock->getVectorPosn()[selectedblock->findIndex()].begin(),
                selectedblock->getVectorPosn()[selectedblock->findIndex()].end(),posn);
            
            if (count >= 2) {
                cur_block->right();
                return;
            }
        }
    }
}

void Board::right() {
    cur_block->right();
    for (auto& outer: cur_block->getVectorPosn()[cur_block->findIndex()]) {
        // out of index
        if (outer.x > 10) {
            cur_block->left();
            return;
        }
    }

    //traverse every block stored in cells
    for (auto& selectedblock : cells) {
        int count = 0;

        //把cur_block里的每一个posn去和存的cell里的一个block里curr_state的4个posn去做比较(std::count)
        for (auto& posn : cur_block->getVectorPosn()[cur_block->findIndex()]) {
            count = std::count(selectedblock->getVectorPosn()[selectedblock->findIndex()].begin(),
                selectedblock->getVectorPosn()[selectedblock->findIndex()].end(),posn);
            
            if (count >= 2) {
                cur_block->left();
                return;
            }
        }
    }
}


void Board::drop() {
    cur_block->drop();
    bool break_status = false;

    while (true) {
        //如果break_status是true代表往上抬一格之后跳出所有for loop重新开始看cells里面的block和他们有没有重合的
        //(因为cur_block更新过了) 如果俩for loop都找完了都没有把break_status变成true说明没有重合
        break_status = false;
        //遍历每一个cells里的block
        for (auto& selectedblock : cells) {
            int count = 0;

            //把cur_block里的每一个posn去和存的cell里的一个block里curr_state的4个posn去做比较(std::count)
            for (auto& outer : (cur_block->getVectorPosn())[cur_block->findIndex()]) {           

                count = std::count(((selectedblock->getVectorPosn())[selectedblock->findIndex()]).begin(),
                    ((selectedblock->getVectorPosn())[selectedblock->findIndex()]).end(),outer);

                if (count >= 2) {
                    cur_block->up();
                    break_status = true;
                    break;
                }
            }
            if (break_status == true) {
                break;
            }
        }
        if (break_status == false) {
            break;
        }
    }
    createBlock();
}

void Board::down() {
    cur_block->down();

    for (auto& outer: cur_block->getVectorPosn()[cur_block->findIndex()]) {
        // out of index
        if (outer.y > 17) {
            cur_block->up();
            return;
        }
    }    

    //traverse every block stored in cells
    for (auto& selectedblock : cells) {
        int count = 0;

        //把cur_block里的每一个posn去和存的cell里的一个block里curr_state的4个posn去做比较(std::count)
        for (auto& posn : cur_block->getVectorPosn()[cur_block->findIndex()]) {
            count = std::count(selectedblock->getVectorPosn()[selectedblock->findIndex()].begin(),
                selectedblock->getVectorPosn()[selectedblock->findIndex()].end(),posn);
            
            if (count >= 2) {
                cur_block->up();
                return;
            }
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
