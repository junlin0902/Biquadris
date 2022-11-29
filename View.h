#ifndef _VIEW_H_
#define _VIEW_H_
#include "window.h"
#include "BoardControl.h"
#include <memory>

class View {
    bool isGraphic;
    std::shared_ptr<Xwindow> xw = nullptr;    

    public:
    explicit View(bool g);
    void displayText(std::shared_ptr<BoardControl> board);
    void displayGraph(std::shared_ptr<BoardControl> board);
    void endGame(std::shared_ptr<BoardControl> board);
    void initGraph();
    void applyBlind(std::shared_ptr<BoardControl> board);
    void removeBlind(std::shared_ptr<BoardControl> board);
};

#endif
