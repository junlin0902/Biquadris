#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <vector>

struct Posn {
    int x, y;
};

class Block {
    protected:
    std::vector<Posn> pos;

    public:
    // helper function to find the min and max value of x of block
    int min_x() const;
    int max_x() const;

    void rotateCW();
    void rotateAW();
    void left();
    void right();
    void drop();
    ~Block() {}
};

class I_block: public Block {
    char c = 'I';
    public:
    I_block() {
        pos = std::vector<Posn>{Posn{0, 3}, Posn{1, 3}, Posn{2, 3}, Posn{3, 3}};
    }
};

class J_block: public Block {
    char c = 'J';
    public:
    J_block() {
        pos = std::vector<Posn>{Posn{0, 2}, Posn{0, 3}, Posn{1, 3}, Posn{2, 3}};
    }
};

class L_block: public Block {
    char c = 'L';
    public:
    L_block() {
        pos = std::vector<Posn>{Posn{0, 3}, Posn{1, 3}, Posn{2, 3}, Posn{2, 2}};
    }
};

class O_block: public Block {
    char c = 'O';
    public:
    O_block() {
        pos = std::vector<Posn>{Posn{0, 2}, Posn{0, 3}, Posn{1, 2}, Posn{0, 3}};
    }
};

class S_block: public Block {
    char c = 'S';
    public:
    S_block() {
        pos = std::vector<Posn>{Posn{0, 3}, Posn{1, 3}, Posn{1, 2}, Posn{2, 2}};
    }
};

class Z_block: public Block {
    char c = 'Z';
    public:
    Z_block() {
        pos = std::vector<Posn>{Posn{0, 2}, Posn{1, 2}, Posn{1, 3}, Posn{2, 3}};
    }
};

class T_block: public Block {
    char c = 'T';
    public:
    T_block() {
        pos = std::vector<Posn>{Posn{0, 2}, Posn{1, 2}, Posn{1, 3}, Posn{2, 2}};
    }
};

#endif
