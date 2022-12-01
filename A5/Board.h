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
    int num_block = 0;

    public:
    Board(std::string);

    // set 
    void setCurBlock(std::shared_ptr<Block> block);
    void setNextBlock(std::shared_ptr<Block> block);
    void setLevel(std::shared_ptr<Level> level);
    void setScore(std::shared_ptr<Score> score);

    // blind effect
    void setBlind();
    void unsetBlind();
    bool getBlind();

    void addCells(std::shared_ptr<Block> star) {cells.push_back(star);}
    std::shared_ptr<Block> getCurBlock();
    std::shared_ptr<Block> getNextBlock();
    std::shared_ptr<Level> getLevel();
    std::shared_ptr<Score> getScore();
    int totalBlock();

    void createBlock();
    
    // helper for finding if there exists Posn{x, y} visible
    bool findPos(int x, int y);
    char findType(int x, int y);

    bool left(); //如果在heavy的情况下down不下去了 is false, else true
    bool right();
    void drop();
    int down(); //1 is true, 0 is false, 2 is false under heavy mode
    void rotateCW();
    void rotateAW();

    int cleanRow();
    void heavy();
    void force(char type);
    void reset();

};


#endif
