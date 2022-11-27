#ifndef _BOARD_H_
#define _BOARD_H_
#include "Block.h"
#include <vector>
#include "Score.h"
#include "Level.h"
#include <memory>

class Board {
    std::vector<std::shared_ptr<Block>> cells;
    std::shared_ptr<Block> cur_block;
    std::shared_ptr<Block> next_block;
    std::shared_ptr<Level> level;
    std::shared_ptr<Score> score;
    bool isBlind = false;
    bool isHeavy = false;
    bool isForce = false;
    int num_block = 0;

    public:
    Board();

    // set 
    void setCurBlock(std::shared_ptr<Block> block);
    void setNextBlock(std::shared_ptr<Block> block);
    void setLevel(std::shared_ptr<Level> level);
    void setScore(std::shared_ptr<Score> score);

    std::shared_ptr<Block> getCurBlock();
    std::shared_ptr<Block> getNextBlock();
    std::shared_ptr<Level> getLevel();
    std::shared_ptr<Score> getScore();
    int totalBlock();

    void createBlock();
    
    // helper for finding if there exists Posn{x, y} visible
    bool findPos(int& x, int& y);

    void left();
    void right();
    void drop();
    void down();

    void cleanRow();
    void blind();
    void heavy();
    void force();
    void reset();
};


#endif
