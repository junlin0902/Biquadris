#include <iostream>
#include "Block.h"
#include "Level.h"
#include "Score.h"
#include "Board.h"
#include <memory>

void print(Board player1) {
    std::cout << "+-----------+" << std::endl;
    for (int i = 0; i < 18; i++) {
        std::cout << '|';
        for (int j = 0; j < 11; j++) {
            if (player1.findPos(j, i)) {
                std::cout << player1.findType(j, i);
            } else {std::cout << ' ';}
        }
        std::cout << '|' << std::endl;
    }
    std::cout << "+-----------+" << std::endl;
}

int main() {
    std::string in1 = "sequence1.txt";
    Board player1 = Board(in1);
    player1.createBlock();
    print(player1);
    player1.rotateCW();
    player1.drop();
    print(player1);
    player1.right();
    player1.right();
    player1.rotateCW();
    print(player1);
    player1.drop();
    print(player1);
    player1.right();
    player1.right();
    player1.right();
    player1.right();
    player1.drop();
    player1.right();
    player1.right();
    player1.right();
    player1.right();
    player1.right();
    player1.right();
    player1.drop();
    player1.right();
    player1.right();
    player1.right();

    player1.drop();
    
    print(player1);
    std::cout << "111" << std::endl;
    player1.cleanRow();
    print(player1);
    player1.drop();
    print(player1);
    player1.right();
    player1.right();
    player1.right();
    player1.right();
    player1.right();
    player1.right();
    player1.right();
    player1.right();
    player1.right();
    player1.drop();
    std::shared_ptr<Block> force2 = std::make_shared<I_block>();
    std::cout << "force2: " << force2 << std::endl;
    player1.force(force2);

    player1.getCurBlock()->rotateCW();
    std::cout << "----------------------" << std::endl;
    std::cout <<(player1.getCurBlock())->findIndex() << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cout <<(player1.getCurBlock()->getVectorPosn()[1][i].x) << std::endl;
        std::cout <<(player1.getCurBlock()->getVectorPosn()[1][i].y) << std::endl;
    }
    
    std::cout << force2 << std::endl;
    player1.right();
    player1.down();
    player1.right();
    player1.down();
    player1.rotateAW();
    player1.left();
    player1.right();
    std::cout << player1.getCurBlock() << std::endl;
    print(player1);
    player1.drop();
    std::cout << player1.getCurBlock() << std::endl;
    print(player1);



}

