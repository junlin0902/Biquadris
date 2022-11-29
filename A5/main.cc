#include <iostream>
#include "Block.h"
#include "Level.h"
#include "Score.h"
#include "Board.h"
#include "View.h"
#include "BoardControl.h"
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
    // Board player1 = Board();
    // player1.createBlock();
    // print(player1);
    // player1.drop();
    // print(player1);
    // player1.right();
    // player1.right();
    // player1.rotateCW();
    // print(player1);
    // player1.drop();
    // print(player1);
    // player1.right();
    // player1.right();
    // player1.right();
    // player1.right();
    // player1.drop();
    // player1.right();
    // player1.right();
    // player1.right();
    // player1.right();
    // player1.right();
    // player1.right();
    // player1.drop();
    // player1.right();
    // player1.right();
    // player1.right();
    // player1.right();
    // player1.right();
    // player1.right();
    // player1.right();
    // player1.right();
    // player1.drop();
    // print(player1);
    // player1.cleanRow();
    // print(player1);
    // std::shared_ptr<Block> force = std::make_shared<I_block>();
    // player1.force(force);
    // print(player1);
    // player1.reset();
    // print(player1);
///////////////////////////
    std::shared_ptr<Board> p1 = std::make_shared<Board>();
    std::shared_ptr<Board> p2 = std::make_shared<Board>();
    bool graph = true;
    BoardControl bc = BoardControl(p1, p2, graph);
    p1->createBlock();
    p2->createBlock();
    // bc.textDisplay();
    p1->setBlind();
    bc.graphDisplay();
    // bc.textDisplay();
    p1->unsetBlind();
    // bc.textDisplay();
    bc.graphDisplay();
    
}

