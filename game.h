#ifndef GAME_H
#define GAME_H

#include <QApplication>

#include <gameview.h>

class Game{

public:
    Game(QApplication *qApplcation);
    void newGame();
    bool isFinished();
    bool isPaused();
    //void loadGame(string filePath);

private:
    QApplication *qApplication;
    void run();
    bool finished = false;
    GameView *view = nullptr;
};

#endif // GAME_H
