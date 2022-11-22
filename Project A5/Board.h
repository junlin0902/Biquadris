#ifndef _BOARD_H_
#define _BOARD_H_
#include "Block.h"
#include <vector>

class Board {
    vector<Block*> cells;
    Block* cur_block;
    Block* next_block;
    int level;
    int score;
    bool isBlind = false;
    bool isHeavy = false;
    bool isForce = false;
    int num_block = 0;

    public:
    void createBlock();
    void cleanRow();
    void blind();
    void heavy();
    void force();
    void end();
};


#endif
