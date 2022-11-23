#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <vector>

struct Posn {
    int x, y;
};

class Block {
    protected:
    char type;
    std::vector<Posn> pos;
    int heavyLevel = 0;

    public:
    // helper function to find the min and max value of x of block to check if
    // this block can move left or right
    int min_x() const;
    int max_x() const;

    void rotateCW();
    void rotateAW();
    void left();
    void right();
    void drop();
    void down();
    char blockType();
    ~Block() {}
};

class I_block: public Block {
    public:
    I_block() {
        type = 'I';
        pos = std::vector<Posn>{Posn{0, 3}, Posn{1, 3}, Posn{2, 3}, Posn{3, 3}};
    }
};

class J_block: public Block {
    public:
    J_block() {
        type = 'J';
        pos = std::vector<Posn>{Posn{0, 2}, Posn{0, 3}, Posn{1, 3}, Posn{2, 3}};
    }
};

class L_block: public Block {
    public:
    L_block() {
        type = 'L';
        pos = std::vector<Posn>{Posn{0, 3}, Posn{1, 3}, Posn{2, 3}, Posn{2, 2}};
    }
};

class O_block: public Block {
    public:
    O_block() {
        type = 'O';
        pos = std::vector<Posn>{Posn{0, 2}, Posn{0, 3}, Posn{1, 2}, Posn{0, 3}};
    }
};

class S_block: public Block {
    public:
    S_block() {
        type = 'S';
        pos = std::vector<Posn>{Posn{0, 3}, Posn{1, 3}, Posn{1, 2}, Posn{2, 2}};
    }
};

class Z_block: public Block {
    public:
    Z_block() {
        type = 'Z';
        pos = std::vector<Posn>{Posn{0, 2}, Posn{1, 2}, Posn{1, 3}, Posn{2, 3}};
    }
};

class T_block: public Block {
    public:
    T_block() {
        type = 'T';
        pos = std::vector<Posn>{Posn{0, 2}, Posn{1, 2}, Posn{1, 3}, Posn{2, 2}};
    }
};

#endif
