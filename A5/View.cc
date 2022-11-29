#include "View.h"
#include "window.h"
#include "BoardControl.h"
#include "Board.h"
#include "Block.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <memory>


// required board size
const int boardRows = 15;
const int totalRows = 18;
const int boardCols = 11;
const int s = 20;                               // side length of 1 single block
const float w = s - 0.01;
const int board_width = boardCols * s;          // width of a board
const int board_height = boardRows * s;         // height of a board
const int header_h = 3 * s;                     // height of header part
const int footer_h = 5 * s;                     // height of footer part
const int inner_s = 5;                       // width of space between b1 and b2
const int outter_s = 5;                     // width of outter space 
const int win_width = 2 * (board_width + outter_s) + inner_s;      // width of the entire window
const int win_height = header_h + board_height + footer_h;     // height of the entire window

const int board_l1 = outter_s;       // left border for P1
const int board_r1 = board_l1 + board_width;       // right border for P1
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
    
    xw = std::make_shared<Xwindow>(win_width, win_height);
    xw->fillRectangle(0, 0, win_width, win_height);         // filled with black
    
    // board 1 & 2
    xw->fillRectangle(board_l1, board_top, board_width, board_height, Xwindow::White);
    xw->fillRectangle(board_l2, board_top, board_width, board_height, Xwindow::White);
    // header & footer 
    xw->fillRectangle(board_l1, 0, board_width, header_h - 0.5, Xwindow::White);
    xw->fillRectangle(board_l2, 0, board_width, header_h - 0.5, Xwindow::White);

    xw->fillRectangle(board_l1, board_d + 1, board_width, footer_h, Xwindow::White);
    xw->fillRectangle(board_l2, board_d + 1, board_width, footer_h, Xwindow::White);

    // strings
    xw->drawString(board_l1 + 1, s, "Level:");
    xw->drawString(board_l2 + 1, s, "Level:");
    xw->drawString(board_l1 + 1, 2 * s, "Score:");
    xw->drawString(board_l2 + 1, 2 * s, "Score:");
    xw->drawString(board_l1 + 1, board_d + s, "Next:");
    xw->drawString(board_l2 + 1, board_d + s, "Next:");

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
        return Xwindow::Black;
    
    case ' ':
        return Xwindow::White;
    }
    return Xwindow::White;
}


void View::displayGraph(std::shared_ptr<Board> b1, std::shared_ptr<Board> b2) {
    // header 
     
    xw->drawString(board_l1 + 1, s, "Level:  " + std::to_string(b1.get()->getLevel().get()->getCurlevel()));
    xw->drawString(board_l2 + 1, s, "Level:  " + std::to_string(b2.get()->getLevel().get()->getCurlevel()));

    xw->drawString(board_l1 + 1, 2 * s, "Score:  " + std::to_string( b1.get()->getScore().get()->getScore()));
    xw->drawString(board_l2 + 1, 2 * s, "Score:  " + std::to_string( b2.get()->getScore().get()->getScore()));

    // board
    for (int i = 0; i < boardRows; i++){
        int color = 0;
        // board 1
        for (int j = 0; j < boardCols; j++){
            // blind && in the range -> black
            if ((b1->getBlind()) && ((i >= 3) && (i <= 12)) && ((j >= 3) && (j <= 9))){
                xw->fillRectangle(board_l1 + (j * s), board_top + (i * s), w, w, Xwindow::Black);
            }
            else {
                color = colortype(b1.get()->findType(j, i));
                xw->fillRectangle(board_l1 + (j * s), board_top + (i * s), w, w, color);
            }  
        }
        // board 2
        for (int j = 0; j < boardCols; j++){
            if ((b2->getBlind()) && ((i >= 3) && (i <= 12)) && ((j >= 3) && (j <= 9))){
                xw->fillRectangle(board_l2 + (j * s), board_top + (i * s), w, w, Xwindow::Black);
            }
            else {
                color = colortype(b2.get()->findType(j, i));
                xw->fillRectangle(board_l2 + (j * s), board_top + (i * s), w, w, color);
            } 
        }
    }

    // Next Block:
    for (int i = 0; i < 4; i++){
        int color;
        for (int j = 0; j < 4; j++){
        // board 1 next block
            if (b1.get()->getNextBlock().get()->findPos(j, i)){
                    color = colortype(b1->getNextBlock().get()->blockType());
                    xw->fillRectangle(board_l1 + 5 * s + (j * s), board_d + s + (i * s), w, w, color);
            }
            // board 2
            if (b2.get()->getNextBlock().get()->findPos(j, i)){
                    color = colortype(b2->getNextBlock().get()->blockType());
                    xw->fillRectangle(board_l2 + 5 * s + (j * s), board_d + s + (i * s), w, w, color);
        }
       } 
    }
}


void View::displayText(std::shared_ptr<Board> b1, std::shared_ptr<Board> b2) {
    // Header part
    std::cout << "Level:" << std::setw(5) << b1->getLevel()->getCurlevel();
    std::cout << "          " ;
    std::cout << "Level:" << std::setw(5) << b2->getLevel()->getCurlevel();
    std::cout << std::endl;
    
    std::cout << "Score:" << std::setw(5) << b1->getScore()->getScore();
    std::cout << "          " ;
    std::cout << "Score:" << std::setw(5) << b2->getScore()->getScore();
    std::cout << std::endl;

    std::cout << "-----------          -----------" << std::endl;
    
    // Board part
    for (int i = 0; i < boardRows; i++) {
        // board 1
        for (int j = 0; j < boardCols; j++){
            // blind && in the range -> cout '?'
            if ((b1->getBlind()) && ((i >= 3) && (i <= 12)) && ((j >= 3) && (j <= 9))){
                std::cout << '?';
            }
            else {
                std::cout << b1->findType(j, i);   
            }     
        }

        std::cout << "          ";

        // board 2
        for (int j = 0; j < boardRows; j++){
            // blind && in the range -> cout '?'
            if ((b2->getBlind()) && ((i >= 3) && (i <= 12)) && ((j >= 3) && (j <= 9))){
                std::cout << '?';
            }
            else {
                std::cout << b2->findType(j, i);
            } 
        }

        std::cout << std::endl;
    }
    
    // Next block
    std::cout << "-----------          -----------" << std::endl;
    std::cout << "Next:                Next:      " << std::endl;
    for (int i = 0; i < 4; i++){
        // next block for board 1
        for (int j = 0; j < 4; j++){
            // there is something in this posn
            if (b1->getNextBlock().get()->findPos(j, i)){
                std::cout << b1->getNextBlock().get()->blockType();
            }
            else {
                std::cout << " ";
            }
        }   // for loop
        std::cout << "                 ";

        // next block for board 2
        for (int j = 0; j < 4; j++){
            // there is something in this posn
            if (b2->getNextBlock().get()->findPos(j, i)){
                std::cout << b2->getNextBlock().get()->blockType();
            }
            else {
                std::cout << " ";
            }
        }   // for loop
        std::cout << "         " << std::endl;
    }   // for loop
}

void View::endGame(std::shared_ptr<Board> b1, std::shared_ptr<Board> b2) {
    int score_1 = b1->getScore().get()->getHscore();
    int score_2 = b2->getScore().get()->getHscore();
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
        xw->fillRectangle(board_l1 + inner_s, board_top + header_h, board_width * 2 - inner_s , 3 * header_h, Xwindow::White);
        xw->drawString(board_l1 + 2 *inner_s, board_top + header_h + s, "Play 1 highest Score" + score_1);
        xw->drawString(board_l1 + 2 *inner_s, board_top + header_h + 2 * s, "Play 2 highest Score" + score_2);
        xw->drawString(board_l1 + 2 *inner_s, board_top + header_h + 3 * s, win);
        
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

