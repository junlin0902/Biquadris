#include "Block.h"
#include <iostream>
#include <algorithm>
#include <math.h>


//=========================================================
// class Block

// get the vector of Posn in class Block
std::vector<std::vector<Posn>> Block::getVectorPosn() const {return pos;}

int Block::findIndex() const {return posIndex;}

void Block::left() {
    for (auto& outer: pos) {
        for (auto& inner: outer) {
            inner.x -= 1;
        }
    }
}

void Block::right() {
    for (auto& outer: pos) {
        for (auto& inner: outer) {
            inner.x += 1;
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

void Block::down() {
    for (auto& outer: pos) {
        for (auto& inner: outer) {
            inner.y += 1;
        }
    }
}

char Block::blockType() const {return type;}


int Block::getHeavyLevel() const {return heavyLevel;}

void Block::setHeavyLevel(int heavy) {heavyLevel = heavy;}

bool Block::findPos(int& x, int& y) {
    if (std::count(pos[posIndex].begin(), pos[posIndex].end(), Posn{x, y, true}) > 0) {
        return true;
    }
    return false;
}

void Block::changeVis(int& x, int& y) {
    for (auto& p: pos[posIndex]) {
        if (p == Posn{x, y, true}) {
            p.visible = false;
        }
    }
}

void Block::changeY(int& x, int& y, int num) {
    for (auto& p: pos[posIndex]) {
        if (p == Posn{x, y, true}) {
            p.y += num;
        }
    }
}

//============================================================
// class I_block
void I_block::rotateCW() {
    rotateTimes += 1;
    posIndex = abs(rotateTimes % 2);
} 

void I_block::rotateAW() {
    rotateTimes -= 1;
    posIndex = abs(rotateTimes % 2);
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
}

void J_block::rotateAW() {
    rotateTimes -= 1;
    int remainder = rotateTimes % 4;
    if (remainder >= 0) {
        posIndex = remainder;
        return;
    }
    posIndex = remainder + 4;
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
}

void L_block::rotateAW() {
    rotateTimes -= 1;
    int remainder = rotateTimes % 4;
    if (remainder >= 0) {
        posIndex = remainder;
        return;
    }
    posIndex = remainder + 4;
}


//=============================================================
// class S_block 
void S_block::rotateCW() {
    rotateTimes += 1;
    posIndex = abs(rotateTimes % 2);
} 

void S_block::rotateAW() {
    rotateTimes -= 1;
    posIndex = abs(rotateTimes % 2);
}


//=============================================================
// class Z_block
void Z_block::rotateCW() {
    rotateTimes += 1;
    posIndex = abs(rotateTimes % 2);
} 

void Z_block::rotateAW() {
    rotateTimes -= 1;
    posIndex = abs(rotateTimes % 2);
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
} 

void T_block::rotateAW() {
    rotateTimes -= 1;
    int remainder = rotateTimes % 4;
    if (remainder >= 0) {
        posIndex = remainder;
        return;
    }
    posIndex = remainder + 4;
}

