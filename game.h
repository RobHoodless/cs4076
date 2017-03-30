#ifndef GAME_H
#define GAME_H

#include <QApplication>

#include "gameview.h"

class Game {
public:
    Game(QApplication * const qApplcation);
    ~Game();
    void newGame();
    bool isFinished() const;
    bool isPaused() const;
    void setFinished(const bool finished);
    void setGameOver(const bool gameOver);
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
