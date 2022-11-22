#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <vector>

struct Posn {
    int x, y;
};

class Block {
    protected:
    std::vector<Posn&> pos;

    public:
    Block(std::vector<Posn&> pos): pos{pos} {}
    virtual void rotateCW() = 0;
    virtual void rotateAW() = 0;
    virtual void left() = 0;
    virtual void right() = 0;
    virtual void drop() = 0;
    virtual ~Block() = 0;
};

class I_block: public Block {
    char c = 'I';

    public:
    void rotateCW() override;
    void rotateAW() override;
    void left() override;
    void right() override;
    void drop() override;
    ~I_block() {};
};

class J_block: public Block {
    char c = 'J';

    public:
    void rotateCW() override;
    void rotateAW() override;
    void left() override;
    void right() override;
    void drop() override;
    ~J_block() {};
};

class L_block: public Block {
    char c = 'L';

    public:
    void rotateCW() override;
    void rotateAW() override;
    void left() override;
    void right() override;
    void drop() override;
    ~L_block() {};
};

class O_block: public Block {
    char c = 'O';

    public:
    void rotateCW() override;
    void rotateAW() override;
    void left() override;
    void right() override;
    void drop() override;
    ~O_block() {};
};

class S_block: public Block {
    char c = 'S';

    public:
    void rotateCW() override;
    void rotateAW() override;
    void left() override;
    void right() override;
    void drop() override;
    ~S_block() {};
};

class Z_block: public Block {
    char c = 'Z';

    public:
    void rotateCW() override;
    void rotateAW() override;
    void left() override;
    void right() override;
    void drop() override;
    ~Z_block() {};
};

class T_block: public Block {
    char c = 'T';

    public:
    void rotateCW() override;
    void rotateAW() override;
    void left() override;
    void right() override;
    void drop() override;
    ~T_block() {};
};

#endif
