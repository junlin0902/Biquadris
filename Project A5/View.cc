#include "View.h"
#include "window.h"
#include "BoardControl.h"
#include "Board.h"
#include "Block.h"
#include <iomanip>
#include <iostream>
#include <string>


// required board size
const int boardRows = 15;
const int totalRows = 18;
const int boardCols = 11;
const int s = 10;                               // side length of 1 single block
const float w = s - 0.01;
const int board_width = boardCols * s;          // width of a board
const int board_height = boardRows * s;         // height of a board
const int header_h = 3 * s;                     // height of header part
const int footer_h = 3 * s;                     // height of footer part
const int inner_s= 3 * s;                       // width of space between b1 and b2
const int outter_s = 2 * s;                     // width of outter space 
const int win_width = 2 * (board_width + outter_s) + inner_s;      // width of the entire window
const int win_height = header_h + board_height + footer_h;     // height of the entire window

const int board_l1 = outter_s;       // left border for P1
const int board_r1 = board_r1 + board_width;       // right border for P1
const int board_l2 = board_r1 + inner_s;       // left border for P2
const int board_r2 = board_l2 + board_width;       // right border for P2
const int board_top = header_h;            // top border
const int board_d = board_top + board_height;     // down border

// Constructor
View::View(bool g): isGraphic{g}, xw{nullptr} {
    if (isGraphic){
        initGraph();
    }
}

// helper 
// initializes the background of the board
void View::initGraph() {
    
    xw = new Xwindow(win_width, win_height);
    xw->fillRectangle(0, 0, win_width, win_height);         // filled with black
    // board 1 & 2
    xw->fillRectangle(board_l1, board_top, board_width, board_height, Xwindow::White);
    xw->fillRectangle(board_l2, board_top, board_width, board_height, Xwindow::White);
    // strings
    xw->drawString(board_l1, s, "Level:");
    xw->drawString(board_l2, s, "Level:");
    xw->drawString(board_l1, 2 * s, "Score:");
    xw->drawString(board_l2, 2 * s, "Score:");
    xw->drawString(board_l1, board_d + s, "Next:");
    xw->drawString(board_l2, board_d + s, "Next:");

}

// Destructor
View::~View() {
    delete xw;
}

// helper function
// return color based on block type
int colortype(char type){
    switch (type)
    {
    case 'I':   
        return Xwindow::Blue;

    case 'J':
        return Xwindow::Brown;

    case 'L':
        return Xwindow::Cyan;

    case 'O':
        return Xwindow::Green;

    case 'S':
        return Xwindow::Magenta;

    case 'Z':
       return Xwindow::Orange;
    
    case 'T':
        return Xwindow::Red;
    
    case '*':
        return Xwindow::White;
    
    case ' ':
        return Xwindow::Black;
    }
}



void View::displayGraph(BoardControl *board) {
    // header 
   // xw->drawString(board_l1, s, "Level: " + board->getBoard1()->getLevel());
   // xw->drawString(board_l2, s, "Level: " + board->getBoard2()->getLevel());

    xw->drawString(board_l1, 2 * s, "Score:");
    xw->drawString(board_l2, 2 * s, "Score:");

    // board
    for (int i = 0; i < board_height; i++){
        int color = 0;
        // board 1
        for (int j = 0; j < board_width; j++){
            color = colortype(board->getBoard1()->blocktype(i, j));
            xw->fillRectangle(board_l1 + (i * s), board_top + (j * s), w, w, color);
        }
        // board 2
        for (int j = 0; j < board_width; j++){
            color = colortype(board->getBoard2()->blocktype(i, j));
            xw->fillRectangle(board_l2 + (i * s), board_top + (j * s), w, w, color);
        }

    }

    // Next Block:
    for (int i = 0; i < 2; i++){
        int color;
       for (int j = 0; j < 4; j++){
        // board 1 next block
        if (board->getBoard1()->getNextBlock().get()->findPos(i, j)){
                color = colortype(board->getBoard1()->getNextBlock().get()->blockType());
                xw->fillRectangle(board_l1 + 5 * s + (i * s), board_d + s + (j * s), w, w, color);
        }
        // board 2
        if (board->getBoard2()->getNextBlock().get()->findPos(i, j)){
                color = colortype(board->getBoard2()->getNextBlock().get()->blockType());
                xw->fillRectangle(board_l2 + 5 * s + (i * s), board_d + s + (j * s), w, w, color);
        }
       } 
    }
}


void View::displayText(BoardControl *board) {
    // Header part
    std::cout << "Level:" << std::setw(5) << board->getBoard1()->getLevel();
    std::cout << "          " ;
    std::cout << "Level:" << std::setw(5) << board->getBoard2()->getLevel();
    std::cout << std::endl;
    
    std::cout << "Score:" << std::setw(5) << board->getBoard1()->getScore();
    std::cout << "          " ;
    std::cout << "Score:" << std::setw(5) << board->getBoard2()->getScore();
    std::cout << std::endl;

    std::cout << "-----------          -----------" << std::endl;
    
    // Board part
    for (int i = 0; i < boardRows; i++) {
        // board 1
        for (int j = 0; j < boardCols; j++){
            std::cout << board->getBoard1()->blocktype(i, j);         
        }

        std::cout << "          ";

        // board 2
        for (int j = 0; j < boardCols; j++){
            std::cout << board->getBoard2()->blocktype(i, j);
        }

        std::cout << std::endl;
    }
    
    // Next block
    std::cout << "-----------          -----------" << std::endl;
    std::cout << "Next:                Next:      " << std::endl;
    for (int i = 0; i < 2; i++){
        // next block for board 1
        for (int j = 0; j < 4; j++){
            // there is something in this posn
            if (board->getBoard1()->getNextBlock().get()->findPos(i, j)){
                std::cout << board->getBoard1()->getNextBlock().get()->blockType();
            }
            else {
                std::cout << " ";
            }
        }   // for loop
        std::cout << "                   ";

        // next block for board 2
        for (int j = 0; j < 4; j++){
            // there is something in this posn
            if (board->getBoard2()->getNextBlock().get()->findPos(i, j)){
                std::cout << board->getBoard2()->getNextBlock().get()->blockType();
            }
            else {
                std::cout << " ";
            }
        }   // for loop
        std::cout << "         " << std::endl;
    }   // for loop
}

void View::endGame(BoardControl *board) {
    int score_1 = board->getBoard1()->getScore().get()->getHscore();
    int score_2 = board->getBoard2()->getScore().get()->getHscore();
    std::string win;

    if (score_1 > score_2){
        win = "Player 1 Wins!";
    }
    else if (score_1 == score_2){
        win = "Tie!";
    }
    else {
        win = "Player 2 Wins!";
    }

    // graphic version
    if (isGraphic){
        
    }
    // text version
    else {
        std::cout << "-----------          -----------" << std::endl;
        std::cout << "Highest Score:    Highest Score:" << std::endl;
        std::cout << score_1 << std::setw(11) << score_2 << std::endl;
        std::cout << std::endl;
        std::cout << win << std::endl;
        std::cout << "-----------          -----------" << std::endl;
    }
}

