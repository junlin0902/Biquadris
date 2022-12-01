#include <iostream>
#include "Block.h"
#include "Level.h"
#include "Score.h"
#include "Board.h"
#include <memory>
#include "BoardControl.h"
#include <sstream>
#include <string>
#include <map>

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

// command identifier
std::string cmdIdentifier(std::string cmd) {
    std::map<std::string, std::string> m {
        {"lef", "left"},
        {"left", "left"},
        
        {"ri", "right"},
        {"rig", "right"},
        {"righ", "right"},
        {"right", "right"},

        {"do", "down"},
        {"dow", "down"},
        {"down", "down"},

        {"dr", "drop"},
        {"dro", "drop"},
        {"drop", "drop"},

        {"cl", "rotateCW"},
        {"clo", "rotateCW"},
        {"cloc", "rotateCW"},
        {"clock", "rotateCW"},
        {"clockw", "rotateCW"},
        {"clockwi", "rotateCW"},
        {"clockwis", "rotateCW"},
        {"clockwise", "rotateCW"},

        {"co", "rotateAW"},
        {"cou", "rotateAW"},
        {"coun", "rotateAW"},
        {"count", "rotateAW"},
        {"counte", "rotateAW"},
        {"counter", "rotateAW"},
        {"counterc", "rotateAW"},
        {"countercl", "rotateAW"},
        {"counterclo", "rotateAW"},
        {"countercloc", "rotateAW"},
        {"counterclock", "rotateAW"},
        {"counterclockw", "rotateAW"},
        {"counterclockwi", "rotateAW"},
        {"counterclockwis", "rotateAW"},
        {"counterclockwise", "rotateAW"},

        {"levelu", "levelup"},
        {"levelup", "levelup"},

        {"leveld", "leveldown"},
        {"leveldo", "leveldown"},
        {"leveldow", "leveldown"},
        {"leveldown", "leveldown"},

        {"n", "norandom"},
        {"no", "norandom"},
        {"nor", "norandom"},
        {"nora", "norandom"},
        {"noran", "norandom"},
        {"norand", "norandom"},
        {"norando", "norandom"},
        {"norandom", "norandom"},

        {"ra", "random"},
        {"ran", "random"},
        {"rand", "random"},
        {"rando", "random"},
        {"random", "random"},

        {"s", "sequence"},
        {"se", "sequence"},
        {"seq", "sequence"},
        {"sequ", "sequence"},
        {"seque", "sequence"},
        {"sequen", "sequence"},
        {"sequenc", "sequence"},
        {"sequence", "sequence"},

        {"re", "restart"},
        {"res", "restart"},
        {"rest", "restart"},
        {"resta", "restart"},
        {"restar", "restart"},
        {"restart", "restart"}
    };

    auto it = m.find(cmd);
    // find in the map
    if (it != m.end()){
        return it->second;
    }
    // cmd does not find in the map
    return cmd;
}


// devide command into num and command
void getPrefix(std::string cmd, int& times, std::string& newCmd , std::string& xxx) {
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
    // no prefix
    if (count == 0) {
        // newCmd = cmd;
        times = 1;
        // return;
    }
    else {
        ss << cmd.substr(0, count);
        ss >> times;
    }

    std::string tempCmd = cmd.substr(count, len - count);
    std::string x;
    std::stringstream cm {tempCmd};
    cm >> tempCmd >> x;

    newCmd = cmdIdentifier(tempCmd);
    xxx = x;
    
}


int main() {
    std::shared_ptr<BoardControl> play = std::make_shared<BoardControl>(std::make_shared<Board>("sequence1.txt"), 
                                                                        std::make_shared<Board>("sequence2.txt"));
    // print(play);
    play->display();

    std::string input;
    std::string command;
    std::string xxx;        // might be file, seed, number etc..
    int times = 1;
    std::cout << "command:" << std::endl;
    while (std::cin >> input) {
        getPrefix(input, times, command, xxx);
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
        } else if (command == "-text") {
            play->noGraph();
        } else if (command == "-seed") {

        } else if (command == "-scriptfile1") {

        } else if (command == "-scriptfile2") {

        } else if (command == "-startlevel") {

        } else if (command == "random") {

        } else if (command == "norandom") {

        } else if (command == "I") {

        } else if (command == "J") {
            
        } else if (command == "L") {
            
        } else if (command == "O") {
            
        } else if (command == "S") {
            
        } else if (command == "Z") {
            
        } else if (command == "T") {
            
        }
        else {
            std::cout << "Invalid Input!" << std::endl;
        }
        // print(play);
        play->display();
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
