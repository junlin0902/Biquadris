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
    // commmand line
    for (int i = 1; i < argc; i++) {
        std::string command = argv[i];
        if (command == "-text") {
            graphic = 1;
        } else if (command == "-seed") {
            i++;
            std::string value = argv[i];
            play->setSeed(stringtoInt(value, value.length()));
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
        if (command == "end") {
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
        } else if (command == "force") {
            char block;
            std::cin >> block;
            play->force(block);
        } else if (command == "restart") {
            std::cout << "This is tie!" << std::endl;
            play->restart();
        } else if (command == "random") {
            play->random();
        } else if (command == "norandom") {
            play->norandom();
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
            if (cmd == "restart") {
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
    }  // while
    std::cout << "Thanks for enjoying Biquadris!" << std::endl;
}
