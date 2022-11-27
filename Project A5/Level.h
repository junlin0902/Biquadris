#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <string>
#include "Block.h"
#include <vector>
#include <memory>

class Level {
    protected:
    std::string filename = "";
    std::vector<char> block; //store the blocks produced in file
    bool is_random;
    int cur_level;
    int curIndex = 0;

    public:
    int getCurlevel();
    void readFile();
    void setRandom(bool ifRandom);
    void setFilename(std::string fname);
    virtual std::shared_ptr<Block> createBlock() = 0;
};

class Level0: public Level {
    public:
    Level0(std::string file) {
        filename = file;
        is_random = false;
        cur_level = 0;
        if (filename != "") {
            readFile();
        }
    }
    std::shared_ptr<Block> createBlock() override;
};

class Level1: public Level {
    public:
    Level1() {
        is_random = true;
        cur_level = 1;
    }
    std::shared_ptr<Block> createBlock() override;
};

class Level2: public Level {
    public:
    Level2() {
        is_random = true;
        cur_level = 2;
    }
    std::shared_ptr<Block> createBlock() override;
};

class Level3: public Level {
    public:
    Level3(std::string file) {
        filename = file;
        is_random = true;
        cur_level = 3;
        if (filename != "") {
            readFile();
        }
    }
    std::shared_ptr<Block> createBlock() override;
};

class Level4: public Level {
    public:
    Level4(std::string file) {
        filename = file;
        is_random = true;
        cur_level = 4;
        if (filename != "") {
            readFile();
        }
    }
    std::shared_ptr<Block> createBlock() override;
};

#endif
