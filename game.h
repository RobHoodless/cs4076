#ifndef GAME_H
#define GAME_H

#include <QApplication>

#include "gameview.h"

class Game {
public:
    Game(QApplication *qApplcation);
    ~Game();
    void newGame();
    bool isFinished() const;
    bool isPaused() const;
    void setFinished(bool finished);
    void setGameOver(bool gameOver);
    bool isGameOver() const;
    //void loadGame(string filePath);

private:
    QApplication *qApplication;
    void run();
    bool finished = false;
    bool gameOver = false;
    GameView *view = nullptr;
};

#endif // GAME_H
