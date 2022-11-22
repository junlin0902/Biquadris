#include "Block.h"

int Block::min_x() const {
    int min = pos[0].x;
    for (auto it: pos) {
        if (it.x < min) {
            min = it.x;
        }
    }
    return min;
};

int Block::max_x() const {
    int max = pos[0].x;
    for (auto it: pos) {
        if (it.x > max) {
            max = it.x;
        }
    }
    return max;
}

void Block::rotateCW() {}

void Block::rotateAW() {}

void Block::left() {
    if (min_x() > 0) {
        for (auto it: pos) {
            it.x -= 1;
        }
    }
}

void Block::right() {
    if (max_x() < 10) {
        for (auto it: pos) {
            it.x += 1;
        }
    }
}

void Block::drop() {}
