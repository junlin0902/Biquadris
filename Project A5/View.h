#ifndef _VIEW_H_
#define _VIEW_H_
#include "window.h"

class View {
    bool isGraphic;
    Xwindow* xw;

    public:
    View();
    ~View();
    void displayText();
    void displayGraph();
    void endGame();
};

#endif