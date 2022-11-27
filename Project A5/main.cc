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
                std::cout << '*';
            } else {std::cout << ' ';}
        }
        std::cout << '|' << std::endl;
    }
    std::cout << "+-----------+" << std::endl;
}

int main() {
    Board player1 = Board();
    player1.createBlock();
    print(player1);
    player1.drop();
    print(player1);
    player1.createBlock();
    print(player1);
}
