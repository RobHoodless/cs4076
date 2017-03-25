#include "gameview.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QKeyEvent>

#include <player.h>

using namespace std;

GameView::GameView(QGraphicsScene *scene, Player *player): QGraphicsView(scene) {
    this->player = player;
    }

void GameView::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Escape) {
        this->paused = true;
    }
    //Qt seems to only support a single key press consumer, so manually passing event to player - should probably change the function call
    //as player is technically no longer subscribed to the event (it seems).
    this->player->keyPressEvent(event);
}

bool GameView::isPaused() { //make this function inline.
    return this->paused;
}

//GameView::~GameView() {
    //Empty implementation for now
//}
