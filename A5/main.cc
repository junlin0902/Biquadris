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
#include <cstdlib>

//===========================helper function=================================================
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

        {"cc", "rotateAW"},
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
void getPrefix(std::string cmd, int& times, std::string& newCmd) {
    int len = cmd.length();
    int count = 0;
    while (count < len) {
        if (isdigit(cmd[count])) {
            count += 1;
        } else {
            break;
        }
    }
    std::stringstream ss;
    // no prefix
    if (count == 0) {
        newCmd = cmd;
        times = 1;
        return;
    }
    newCmd = cmd.substr(count, len - count);
    ss << cmd.substr(0, count);
    ss >> times;
}

// transfer string to int
int stringtoInt(std::string string, int i) {
    int num = 0;
    int times = 1;
    for (int j = i - 1; j >= 0; j--) {
        if (string[j] == '-') {
            return -num;
        } else {
            num += times * (string[j] - '0');
            times *= 10;
        }
    }
    return num;
}

// list of avaliable commands
void help() {
    std::cout << "=========================================================================" << std::endl;
    std::cout << " left -------------- Moves current block one cell to the left" << std::endl;
    std::cout << " right ------------- Moves current block one cell to the right" << std::endl;
    std::cout << " down -------------- Moves current block one cell downward" << std::endl;
    std::cout << " clockwise --------- Rotates current block 90 degrees clockwise " << std::endl;
    std::cout << " counterclockwise -- Rotates current block 90 degrees counterclockwise" << std::endl;
    std::cout << " drop -------------- Drops the current block" << std::endl;
    std::cout << " levelup ----------- Increases the difficulty level of the game by one" << std::endl;
    std::cout << " leveldown --------- Decreases the difficulty level of the game by one" << std::endl;
    std::cout << " restart ----------- Clears the board and starts a new game" << std::endl;
    std::cout << "=========================================================================" << std::endl;
    std::cout << " You can type only part of a command, as long as it is distinct from" << std::endl;
    std::cout << " other commands.   " << std::endl;
    std::cout << "      i.e. 'lef' is enough for 'left'" << std::endl;
    std::cout << " Commands can take a multiplier prefix, indicating that command should" << std::endl;
    std::cout << " be executed some number of times." << std::endl;
    std::cout << "      i.e. '3ri' means move to the right by 3 cells" << std::endl;
    std::cout << "=========================================================================" << std::endl;
    
}


//============================================main=========================================================================
int main(int argc, const char *argv[]) {
    std::cout << "Are you ready to begin? Type p to begin Biquadris else to end" << std::endl;
    char begin;
    std::cin >> begin;
    if (begin != 'p') {return 1;}

    int graphic = 0;
    std::string file1 = "sequence1.txt";
    std::string file2 = "sequence2.txt";
    std::shared_ptr<BoardControl> play = std::make_shared<BoardControl>(std::make_shared<Board>(file1), 
                                                                        std::make_shared<Board>(file2));
    
    std::cout << "Type 'help' to see a list of command." << std::endl;
    
    // commmand line
    for (int i = 1; i < argc; i++) {
        std::string command = argv[i];
        if (command == "-text") {
            graphic = 1;
        } else if (command == "-seed") {
            i++;
            std::string value = argv[i];
            srand(stringtoInt(value, value.length()));
            // unset curblock and nextblock
            play->getBoard1()->resetBlockonly();
            // reset counter only for level 4
            play->getBoard1()->getLevel()->resetRound();
            // need to reset curblock and nextblock
            play->getBoard1()->createBlock();

            play->getBoard2()->resetBlockonly();
            play->getBoard1()->getLevel()->resetRound();
            play->getBoard2()->createBlock();
        } else if (command == "-scriptfile1") {
            i++;
            file1 = argv[i];
            play->getBoard1()->getLevel()->setFilename(file1);
        } else if (command == "-scriptfile2") {
            i++;
            file2 = argv[i];
            play->getBoard1()->getLevel()->setFilename(file1);
        } else if (command == "-startlevel") {
            i++;
            std::string l = argv[i];
            int len = l.length();
            int level = stringtoInt(l, len);
            // set level here;
            play->levelup(level);
            play->changeRound();
            play->levelup(level);
            play->changeRound();
        }
    }

    if (graphic == 0) {
        play->needGraph();
    }
    // print(play);
    play->display();


    std::string input;
    std::string command;
    int times = 1;
    bool endStatus = false;
    std::cout << "command:" << std::endl;
    while (std::cin >> input) {
        getPrefix(input, times, command);
        command = cmdIdentifier(command);
        if (play->if_firststep() == false) { // this is temp can be deleted and also isfirststep
            endStatus = true;
        } else if (command == "end") {
            char end;
            play->endgame();
            std::cout << "Press q to exit." << std::endl;
            std::cin >> end;
            if (end == 'q') {
                break;
            }
        } else if (command == "left") {
            try {
            play->left(times);
            } catch (std::string endmsg) {
                endStatus = true;
            }
        } else if (command == "right") {
            try {
            play->right(times);
            } catch (std::string endmsg) {
                endStatus = true;
            }
        } else if (command == "down") {
            try {
            play->down(times);
            } catch (std::string endmsg) {
                endStatus = true;
            }
        } else if (command == "drop") {
            try {
            play->drop();
            } catch (std::string endmsg) {
                endStatus = true;
            }
        } else if (command == "rotateCW") {
            try {
            play->rotateCW(times);
            } catch (std::string endmsg) {
                endStatus = true;
            }
        } else if (command == "rotateAW") {
            try {
            play->rotateAW(times);
            } catch (std::string endmsg) {
                endStatus = true;
            }
        } else if (command == "levelup") {
            play->levelup(times);
        } else if (command == "leveldown") {
            play->leveldown(times);

        // this is just for testing special action 
        // need to be deleted
        } else if (command == "force") {
            char block;
            std::cin >> block;
            play->force(block);
        } else if (command == "heavy") {
            play->heavy();
        } else if (command == "blind") {
            play->applyBlind();
        
        
        
        } else if (command == "restart") {
            play->restart();
        } else if (command == "random") {
            play->random();
        } else if (command == "norandom") {
            play->norandom();
        } else if (command == "help") {
            help();
        } else {
            std::cout << "Invalid Input!" << std::endl;
        }


        // print(play);
        play->display();
        if (endStatus) {
            std::string cmd;
            
            std::cout << "Game is end!" << std::endl;
            // who win here
            /*int s1 = play->getBoard1()->getScore()->getScore();
            int s2 = play->getBoard2()->getScore()->getScore();
            std::cout << "Score for player1: " << s1 << std::endl;
            std::cout << "Score for player2: " << s2 << std::endl;
            if (s1 > s2) {std::cout << "WINNER is player1!!" << std::endl;}
            else if (s1 < s2) {std::cout << "WINNER is player2!!" << std::endl;}
            else {std::cout << "This is tie!" << std::endl;}
            std::cout << std::endl;*/

            std::cout << "Choose restart or end?" << std::endl;
            std::cin >> cmd;
            if (cmd[0] == 'r' || cmd[0] == 'R') {
                endStatus = false;
                play->restart();
                play->display();
            } else {
                // testing purpose
                char end;
                play->endgame();
                std::cout << "Press q to exit." << std::endl;
                std::cin >> end;
                if (end == 'q') {
                    break;
                }
            }
        }
        std::cout << "command:" << std::endl;
    }
    std::cout << "Thanks for enjoying Biquadris!" << std::endl;
}
