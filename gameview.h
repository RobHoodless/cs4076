#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsScene>
#include <QGraphicsView>

#include <player.h>

class GameView : public QGraphicsView {
public:
    GameView(QGraphicsScene *scene, Player *player);
    //~GameView();
    void keyPressEvent(QKeyEvent *event);
    bool isPaused() const;

private:
    bool paused = false;
    Player *player;
};

#endif // GAMEVIEW_H
