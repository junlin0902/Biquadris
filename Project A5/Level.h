#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <string>
#include "Block.h"

class Level {
    protected:
    int cur_level;
    bool is_random;
    std::string filename;

    public:
    ~Level();

    int getCurlevel();
    void readFile();
    void setRandom(bool ifRandom);
    void setFilename(std::string fname);
    virtual void level_up();
    virtual void level_down();
    virtual Block* createBlock() = 0;
};

class Level0: public Level {
    void level_up() override;
    void level_down() override;
    Block* createBlock() override;
};

class Level1: public Level {
    void level_up() override;
    void level_down() override;
    Block* createBlock() override;
};

class Level2: public Level {
    void level_up() override;
    void level_down() override;
    Block* createBlock() override;
};

class Level3: public Level {
    void level_up() override;
    void level_down() override;
    Block* createBlock() override;
};

class Level4: public Level {
    void level_up() override;
    void level_down() override;
    Block* createBlock() override;
};

#endif
