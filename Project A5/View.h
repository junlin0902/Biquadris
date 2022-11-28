#ifndef _VIEW_H_
#define _VIEW_H_
#include "window.h"

class View {
    bool isGraphic;
    Xwindow* xw = nullptr;

    public:
    explicit View(bool g);
    ~View();
    void displayText(BoardControl *board);
    void displayGraph(BoardControl *board);
    void endGame(BoardControl *board);
    void initGraph();
    void applyBlind(BoardControl *board);
    void removeBlind(BoardControl *board);
};

#endif
