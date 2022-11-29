#include "Level.h"
#include <fstream>
#include <cstdlib>
#include <iostream>

//=============================================================
// class Level
int Level::getCurlevel() {return cur_level;}

void Level::readFile() {
    if (filename == "") {return;}
    std::ifstream iss{filename};
    char blockIn;
    while (iss >> blockIn) {
        block.push_back(blockIn);
    }
}

void Level::changeRandom() {
    if (is_random) {
        is_random = false;
        return;
    }
    is_random = true;
}

void Level::setFilename(std::string fname) {filename = fname;}

//=============================================================
// class Level0
std::shared_ptr<Block> Level0::createBlock() {
    int size = block.size();
    if (curIndex == size) {
        curIndex = 0;
    }
    curIndex += 1;
    if (block[curIndex - 1] == 'I') {
        return std::make_shared<I_block>();
    } else if (block[curIndex - 1] == 'J') {
        return std::make_shared<J_block>();
    } else if (block[curIndex - 1] == 'L') {
        return std::make_shared<L_block>();
    } else if (block[curIndex - 1] == 'O') {
        return std::make_shared<O_block>();
    } else if (block[curIndex - 1] == 'S') {
        return std::make_shared<S_block>();
    } else if (block[curIndex - 1] == 'Z') {
        return std::make_shared<Z_block>();
    } else {
        return std::make_shared<T_block>();
    }
}


//=============================================================
// class Level1
std::shared_ptr<Block> Level1::createBlock() {
    int num = rand() % 6;
    if (num == 0) {
        return std::make_shared<I_block>();
    } else if (num == 1) {
        return std::make_shared<J_block>();
    } else if (num == 2) {
        return std::make_shared<L_block>();
    } else if (num == 3) {
        return std::make_shared<O_block>();
    } else if (num == 4) {
        return std::make_shared<T_block>();
    }
    int num2 = rand() % 2;
    if (num2 == 0) {
        return std::make_shared<S_block>();
    }
    return std::make_shared<Z_block>();
}


//=============================================================
// class level2
std::shared_ptr<Block> Level2::createBlock() {
    int num = rand() % 7;
    if (num == 0) {
        return std::make_shared<I_block>();
    } else if (num == 1) {
        return std::make_shared<J_block>();
    } else if (num == 2) {
        return std::make_shared<L_block>();
    } else if (num == 3) {
        return std::make_shared<O_block>();
    } else if (num == 4) {
        return std::make_shared<T_block>();
    } else if (num == 5) {
        return std::make_shared<S_block>();
    } else {
        return std::make_shared<Z_block>();
    }
}


//=============================================================
std::shared_ptr<Block> Level3::createBlock() {
    std::shared_ptr<Block> b;
    if (is_random) {
        int num = rand() % 9;
        if (num == 0 || num == 1) {
            b = std::make_shared<S_block>();
        } else if (num == 2 || num == 3) {
            b = std::make_shared<Z_block>();
        } else if (num == 4) {
            b = std::make_shared<I_block>();
        } else if (num == 5) {
            b = std::make_shared<J_block>();
        } else if (num == 6) {
            b = std::make_shared<L_block>();
        } else if (num == 7) {
            b = std::make_shared<O_block>();
        } else {
            b = std::make_shared<T_block>();        
        }
    } else {
        int size = block.size();
        if (curIndex == size) {
            curIndex = 0;
        }
        curIndex += 1;
        if (block[curIndex - 1] == 'I') {
            b = std::make_shared<I_block>();
        } else if (block[curIndex] == 'J') {
            b = std::make_shared<J_block>();
        } else if (block[curIndex] == 'L') {
            b = std::make_shared<L_block>();
        } else if (block[curIndex] == 'O') {
            b = std::make_shared<O_block>();
        } else if (block[curIndex] == 'S') {
            b = std::make_shared<S_block>();
        } else if (block[curIndex] == 'Z') {
            b = std::make_shared<Z_block>();
        } else {
            b = std::make_shared<T_block>();
        }
    }
    b->setHeavyLevel(1);
    return b;
}


//=============================================================
std::shared_ptr<Block> Level4::createBlock() {
    std::shared_ptr<Block> b;
    if (is_random) {
        int num = rand() % 9;
        if (num == 0 || num == 1) {
            b = std::make_shared<S_block>();
        } else if (num == 2 || num == 3) {
            b = std::make_shared<Z_block>();
        } else if (num == 4) {
            b = std::make_shared<I_block>();
        } else if (num == 5) {
            b = std::make_shared<J_block>();
        } else if (num == 6) {
            b = std::make_shared<L_block>();
        } else if (num == 7) {
            b = std::make_shared<O_block>();
        } else {
            b = std::make_shared<T_block>();        
        }
    } else {
        int size = block.size();
        if (curIndex == size) {
            curIndex = 0;
        }
        curIndex += 1;
        if (block[curIndex - 1] == 'I') {
            b = std::make_shared<I_block>();
        } else if (block[curIndex] == 'J') {
            b = std::make_shared<J_block>();
        } else if (block[curIndex] == 'L') {
            b = std::make_shared<L_block>();
        } else if (block[curIndex] == 'O') {
            b = std::make_shared<O_block>();
        } else if (block[curIndex] == 'S') {
            b = std::make_shared<S_block>();
        } else if (block[curIndex] == 'Z') {
            b = std::make_shared<Z_block>();
        } else {
            b = std::make_shared<T_block>();
        }
    }
    b->setHeavyLevel(1);
    return b;
}


//=============================================================
// just for testing
/*int main() {
    std::vector<std::shared_ptr<Block>> b;
    std::shared_ptr<Level> l1 = std::make_shared<Level2>(Level2{});
    for (int i = 0; i < 5; i++) {
        b.push_back(l1->createBlock());
    }
    for (auto it: b) {
        std::cout << it->blockType() <<' ';
    }
    std::cout << std::endl;
}*/
