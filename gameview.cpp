#include "gameview.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>

#include "player.h"
#include "room.h"

using namespace std;

GameView::GameView(QGraphicsScene * const scene, Player * const player, Room *room): QGraphicsView(scene) {
    this->player = player;
    this->room = room;
}

void GameView::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        this->paused = true;
    }

    //Qt seems to only support a single key press consumer, so manually passing event to player.
    this->player->keyPressEvent(event);
}

bool GameView::isPaused() const {
    return this->paused;
}

GameView::~GameView() {
    //Empty implementation for now
}
