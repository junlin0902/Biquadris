#include "Block.h"
#include <iostream>
#include <algorithm>
#include <math.h>

extern const int totalRow = 17;
extern const int totalCol = 10;

//=========================================================
// class Block

// get the vector of Posn in class Block
std::vector<std::vector<Posn>> Block::getVectorPosn() const {return pos;}

int Block::findIndex() const {return posIndex;}

void Block::left() {
    for (auto& outer: pos) {
        for (auto& inner: outer) {
            inner.x -= 1;
            inner.y += heavyLevel;
        }
    }
}

void Block::right() {
    for (auto& outer: pos) {
        for (auto& inner: outer) {
            inner.x += 1;
            inner.y += heavyLevel;
        }
    }
}

void Block::up() {
    for (auto& outer: pos) {
        for (auto& inner: outer) {
            inner.y -= 1;
        }
    }
}

void Block::drop() {
    int maxy = -1;
    for (auto& outer: pos) {
        for (auto& inner: outer) {
            if (maxy < inner.y) {
                maxy = inner.y;
            }
        }
    }
    int length = totalRow - maxy;
    for (auto& outer: pos) {
        for (auto& inner: outer) {
            inner.y += length;
        }
    } 
}

void Block::down() {
    for (auto& outer: pos) {
        for (auto& inner: outer) {
            inner.y += 1;
            inner.y += heavyLevel;
        }
    }
}

char Block::blockType() const {return type;}

int Block::getHeavyLevel() const {return heavyLevel;}

void Block::setHeavyLevel(int heavy) {heavyLevel = heavy;}

//============================================================
// class I_block
void I_block::rotateCW() {
    rotateTimes += 1;
    posIndex = abs(rotateTimes % 2);
    for (auto& outer: pos) {
        for (auto& inner: outer) {
            inner.y += heavyLevel;
        }
    }
} 

void I_block::rotateAW() {
    rotateTimes -= 1;
    posIndex = abs(rotateTimes % 2);
    for (auto& outer: pos) {
        for (auto& inner: outer) {
            inner.y += heavyLevel;
        }
    }
}

//=============================================================
// class J_block
void J_block::rotateCW() {
    rotateTimes += 1;
    int remainder = rotateTimes % 4;
    if (remainder >= 0) {
        posIndex = remainder;
        return;
    }
    posIndex = remainder + 4;
    for (auto& outer: pos) {
        for (auto& inner: outer) {
            inner.y += heavyLevel;
        }
    }
}

void J_block::rotateAW() {
    rotateTimes -= 1;
    int remainder = rotateTimes % 4;
    if (remainder >= 0) {
        posIndex = remainder;
        return;
    }
    posIndex = remainder + 4;
    for (auto& outer: pos) {
        for (auto& inner: outer) {
            inner.y += heavyLevel;
        }
    }
}

//=============================================================
// class L_block
void L_block::rotateCW() {
    rotateTimes += 1;
    int remainder = rotateTimes % 4;
    if (remainder >= 0) {
        posIndex = remainder;
        return;
    }
    posIndex = remainder + 4;
    for (auto& outer: pos) {
        for (auto& inner: outer) {
            inner.y += heavyLevel;
        }
    }
}

void L_block::rotateAW() {
    rotateTimes -= 1;
    int remainder = rotateTimes % 4;
    if (remainder >= 0) {
        posIndex = remainder;
        return;
    }
    posIndex = remainder + 4;
    for (auto& outer: pos) {
        for (auto& inner: outer) {
            inner.y += heavyLevel;
        }
    }
}


//=============================================================
// class S_block 
void S_block::rotateCW() {
    rotateTimes += 1;
    posIndex = abs(rotateTimes % 2);
    for (auto& outer: pos) {
        for (auto& inner: outer) {
            inner.y += heavyLevel;
        }
    }
} 

void S_block::rotateAW() {
    rotateTimes -= 1;
    posIndex = abs(rotateTimes % 2);
    for (auto& outer: pos) {
        for (auto& inner: outer) {
            inner.y += heavyLevel;
        }
    }
}


//=============================================================
// class Z_block
void Z_block::rotateCW() {
    rotateTimes += 1;
    posIndex = abs(rotateTimes % 2);
    for (auto& outer: pos) {
        for (auto& inner: outer) {
            inner.y += heavyLevel;
        }
    }
} 

void Z_block::rotateAW() {
    rotateTimes -= 1;
    posIndex = abs(rotateTimes % 2);
    for (auto& outer: pos) {
        for (auto& inner: outer) {
            inner.y += heavyLevel;
        }
    }
}


//==============================================================
// class T_block
void T_block::rotateCW() {
    rotateTimes += 1;
    int remainder = rotateTimes % 4;
    if (remainder >= 0) {
        posIndex = remainder;
        return;
    }
    posIndex = remainder + 4;
    for (auto& outer: pos) {
        for (auto& inner: outer) {
            inner.y += heavyLevel;
        }
    }
} 

void T_block::rotateAW() {
    rotateTimes -= 1;
    int remainder = rotateTimes % 4;
    if (remainder >= 0) {
        posIndex = remainder;
        return;
    }
    posIndex = remainder + 4;
    for (auto& outer: pos) {
        for (auto& inner: outer) {
            inner.y += heavyLevel;
        }
    }
}


//==============================================================
// just for testing
/*void print(std::shared_ptr<Block> block1) {
    std::vector<std::vector<Posn>> temp = block1->getVectorPosn();
    int index = block1->findIndex();
    std::cout << "+------+" << std::endl;
    for (int i = 0; i < 6; i++) {
        std::cout << '|';
        for (int j = 0; j < 6; j++) {
            if (std::count(temp[index].begin(), temp[index].end(), Posn{j, i}) != 0) {
                std::cout << block1->blockType();
            } else {
                std::cout << ' ';
            }
        }
        std::cout << '|' <<std::endl;
    }
    std::cout << "+------+" << std::endl;
    for (auto it: temp[index]) {
        std::cout << "Posn:" << it.x << ' ' << it.y << std::endl;
    }
}


int main() {
    std::shared_ptr<Block> b1 = std::make_shared<I_block>(I_block{});
    std::shared_ptr<Block> b2 = std::make_shared<T_block>(T_block{});
    print(b2);
    b2->left();
    print(b2);
    b2->right();
    b2->right();
    print(b2);
    b2->down();
    print(b2);
    b2->rotateAW();
    print(b2);
    b2->rotateCW();
    b2->rotateCW();
    print(b2);
    b2->rotateCW();
    print(b2);
}*/
