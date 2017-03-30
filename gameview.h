#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsScene>
#include <QGraphicsView>

#include "player.h"
#include "room.h"

class GameView : public QGraphicsView {
public:
    GameView(QGraphicsScene *const scene, Player *const player, Room *room);
    ~GameView();
    void keyPressEvent(QKeyEvent *event);
    bool isPaused() const;

private:
    bool paused = false;
    Player *player;
    Room *room;
};

#endif // GAMEVIEW_H
