#include <iostream>
#include "Block.h"
#include "Level.h"
#include "Score.h"
#include "Board.h"
#include <memory>
#include "BoardControl.h"
#include <sstream>
#include <string>

void print(std::shared_ptr<BoardControl> player1) {
    std::cout << "Board1:" << "        " << "Board2:" << std::endl;
    std::cout << "+-----------+" << "  " << "+-----------+" << std::endl;
    for (int i = 0; i < 18; i++) {
        std::cout << '|';
        for (int j = 0; j < 11; j++) {
            if (player1->getBoard1()->findPos(j, i)) {
                std::cout << player1->getBoard1()->findType(j, i);
            } else {std::cout << ' ';}
        }
        std::cout << '|' << "  ";

        //second board
        std::cout << '|';
        for (int j = 0; j < 11; j++) {
            if (player1->getBoard2()->findPos(j, i)) {
                std::cout << player1->getBoard2()->findType(j, i);
            } else {std::cout << ' ';}
        }
        std::cout << '|' << std::endl;        
    }
    std::cout << "+-----------+" << "  " << "+-----------+" << std::endl;
    std::cout << "level         |player1:" << player1->getBoard1()->getLevel()->getCurlevel()
              << " player2:" << player1->getBoard2()->getLevel()->getCurlevel() << std::endl;
    std::cout << "current score |player1:" << player1->getBoard1()->getScore()->getScore() 
              << " player2:" << player1->getBoard2()->getScore()->getScore() << std::endl;
    std::cout << "high score    |player1:" << player1->getBoard1()->getScore()->getHscore() 
              << " player2:" << player1->getBoard2()->getScore()->getHscore() << std::endl;
}

// devide command into num and command
void getPrefix(std::string cmd, int& times, std::string& newCmd) {
    int len = cmd.length();
    int count = 0;
    while (count < len) {
        if (cmd[count] == '1' || cmd[count] == '2' || cmd[count] == '3' || cmd[count] == '4' || cmd[count] == '5' ||
            cmd[count] == '6' || cmd[count] == '7' || cmd[count] == '8' || cmd[count] == '9') {
            count += 1;
        } else {
            break;
        }
    }
    std::stringstream ss;
    if (count == 0) {
        newCmd = cmd;
        times = 1;
        return;
    }
    newCmd = cmd.substr(count, len - count);
    ss << cmd.substr(0, count);
    ss >> times;
}


int main() {
    std::shared_ptr<BoardControl> play = std::make_shared<BoardControl>(std::make_shared<Board>("sequence1.txt"), 
                                                                        std::make_shared<Board>("sequence2.txt"));
    // print(play);
    play->textDisplay();
    play->graphDisplay();

    std::string input;
    std::string command;
    int times = 1;
    std::cout << "command:" << std::endl;
    while (std::cin >> input) {
        getPrefix(input, times, command);
        if (command == "end") {
            break;
        } else if (command == "left") {
            play->left(times);
        } else if (command == "right") {
            play->right(times);
        } else if (command == "down") {
            play->down(times);
        } else if (command == "drop") {
            play->drop();
        } else if (command == "rotateCW") {
            play->rotateCW(times);
        } else if (command == "rotateAW") {
            play->rotateAW(times);
        } else if (command == "heavy") {
            play->heavy();
        } else if (command == "levelup") {
            play->levelup(times);
        } else if (command == "leveldown") {
            play->leveldown(times);
        } else if (command == "force") {
            char block;
            std::cin >> block;
            play->force(block);
        } else if (command == "restart") {
            std::cout << "This is tie!" << std::endl;
            play->restart();
        }
        // print(play);
        play->textDisplay();
        play->graphDisplay();
        if (play->find_whowin() != 0) {
            std::cout << "game is end!" << std::endl;
            std::cout << "winner is player" << play->find_whowin() << std::endl;
            std::cout << "type restart or end" << std::endl;
            std::string cmd;
            std::cin >> cmd;
            if (cmd == "end") {
                break;
            } else if (cmd == "restart") {
                play->restart();
            }
        }
        std::cout << "command:" << std::endl;
    }
}
