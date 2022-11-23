#ifndef _BOARD_H_
#define _BOARD_H_
#include "Block.h"
#include <vector>
#include "Score.h"
#include "Level.h"

class Board {
    vector<Block*> cells;
    Block* cur_block;
    Block* next_block;
    Level* level;
    Score* score;
    bool isBlind = false;
    bool isHeavy = false;
    bool isForce = false;
    int num_block = 0;

    public:
    Board();
    ~Board();

    // set 
    void setCurBlock(Block* block);
    void setNextBlock(Block* block);
    void setLevel(int level);
    void setScore(int score);

    Block* getCurBlock();
    Block* getNextBlock();
    Level* getLevel();
    Score* getScore();
    int totalBlock();

    void createBlock();
    void cleanRow();
    void blind();
    void heavy();
    void force();
    void reset();
};


#endif
