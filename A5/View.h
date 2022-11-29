#ifndef _VIEW_H_
#define _VIEW_H_
#include "window.h"
#include <memory>
#include "Board.h"

class View {
    bool isGraphic;
    std::shared_ptr<Xwindow> xw = nullptr;    

    public:
    explicit View(bool g);
    void displayText(std::shared_ptr<Board> b1, std::shared_ptr<Board> b2);
    void displayGraph(std::shared_ptr<Board> b1, std::shared_ptr<Board> b2);
    void endGame(std::shared_ptr<Board> b1, std::shared_ptr<Board> b2);
    void initGraph();
    void applyBlind_graph(std::shared_ptr<Board> board);
    void removeBlind_graph(std::shared_ptr<Board> board);
    void applyBlind_text(std::shared_ptr<Board> board);
    void removeBlind_text(std::shared_ptr<Board> board);
};

#endif
