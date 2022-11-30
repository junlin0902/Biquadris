#include <iostream>
#include "Block.h"
#include "Level.h"
#include "Score.h"
#include "Board.h"
#include <memory>
#include "BoardControl.h"

void print(BoardControl player1) {
    std::cout << "Board1:" << "        " << "Board2:" << std::endl;
    std::cout << "+-----------+" << "  " << "+-----------+" << std::endl;
    for (int i = 0; i < 18; i++) {
        std::cout << '|';
        for (int j = 0; j < 11; j++) {
            if (player1.getBoard1()->findPos(j, i)) {
                std::cout << player1.getBoard1()->findType(j, i);
            } else {std::cout << ' ';}
        }
        std::cout << '|' << "  ";

        //second board
        std::cout << '|';
        for (int j = 0; j < 11; j++) {
            if (player1.getBoard2()->findPos(j, i)) {
                std::cout << player1.getBoard2()->findType(j, i);
            } else {std::cout << ' ';}
        }
        std::cout << '|' << std::endl;        
    }
    std::cout << "+-----------+" << "  " << "+-----------+" << std::endl;

}

int main() {
    std::string in1 = "sequence1.txt";
    std::string in2 = "sequence2.txt";
    BoardControl play = BoardControl(std::make_shared<Board>(in1), std::make_shared<Board>(in2));
    print(play);

    play.right(20);
    print(play);
    play.down(20);
    play.left(1);
    print(play);
    play.drop();
    play.right(4);
    print(play);
    play.left(20);
    play.drop();
    print(play);
    play.getBoard1()->heavy();
    play.right(1);
    print(play);
    play.right(4);
    print(play);
    play.right(1);
    print(play);
    play.right(1);
    print(play);
    play.down(20);
    print(play);
    play.right(20);
    print(play);
    play.drop();
    play.drop();
    play.drop();
    play.drop();
    play.drop();
    play.drop();
    play.drop();
    play.drop();
    play.drop();
    play.drop();
    print(play);
    play.drop();
    play.drop();
    play.drop();
    play.drop();
    play.drop();
    play.drop();
    play.right(1);
    play.drop();
    print(play);
    // play.drop();
    // play.levelup(1);
    // play.drop();
    // print(play);
    // play.right(4);
    // play.drop();
    // play.drop();
    // print(play);
    // play.getBoard1()->heavy();
    // print(play);
    // play.right(1);
    // print(play);
    // play.right(1);
    // print(play);
    // play.right(1);
    // print(play);

    /*play.drop();
    play.levelup(1);
    play.drop();
    print(play);
    play.rotateCW(2);
    play.right(3);
    play.drop();
    play.right(2);
    play.drop();
    print(play);
    play.right(5);
    play.drop();
    play.getBoard2()->force('I');
    print(play);
    play.getBoard1()->force('Z');
    print(play);
    play.right(5);
    play.drop();
    print(play);
    play.right(7);
    play.drop();
    play.right(9);
    play.drop();
    print(play);
    play.right(1);
    play.drop();
    play.right(3);
    play.drop();
    print(play);
    play.right(3);
    play.drop();
    play.right(6);
    play.drop();
    print(play);
    play.getBoard1()->force('S');
    play.rotateCW(1);
    play.right(20);
    play.drop();
    print(play);*/
    /*print(play);
    std::cout << play.getBoard1()->getCurBlock() << std::endl;
    std::shared_ptr<Block> i = std::make_shared<I_block>();
    play.getBoard1()->force('I');
    std::cout << play.getBoard1()->getCurBlock() << std::endl;
    print(play);
    play.rotateAW(1);
    print(play);*/
    std::cout << play.getBoard1()->getScore()->getScore() << ' ' << play.getBoard2()->getScore()->getScore() << std::endl;
}
