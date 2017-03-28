#include "player.h"

#include <QKeyEvent>
#include <QDebug>

#include <item.h>
#include <collidableentity.h>
#include "item.h"

Player::Player(int maxX, int maxY) : MobileEntity(":/images/dragon.png", maxX, maxY) {
    // Make player focusable
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();
}

void Player::keyReleaseEvent(QKeyEvent *event) {
    keysPressed -= event->key();

    if (event->key() == Qt::Key_W) {
        movingNorth = false;
    }
    if (event->key() == Qt::Key_A){
        movingWest = false;
    }
    if (event->key() == Qt::Key_D) {
        movingEast = false;
    }
    if (event->key() == Qt::Key_S) {
        movingSouth = false;
    }
}

void Player::keyPressEvent(QKeyEvent *event) {
    keysPressed += event->key();
    processKeys();
}

void Player::processKeys() {
    if (keysPressed.contains(Qt::Key_W)) {
        movingNorth = true;
    }
    if (keysPressed.contains(Qt::Key_A)){
        movingWest = true;
    }
    if (keysPressed.contains(Qt::Key_D) ) {
        movingEast = true;
    }
    if (keysPressed.contains(Qt::Key_S) ) {
        movingSouth = true;
    }
}

void Player::draw() {
    this->setPixmap(standing.getPixmap());
}

void Player::move() {
    steps++;
    if (movingWest) {
        int nextX = ((((this->x() - 10)) < 0) ? 0 : (this->x() - 10));
        this->setPos(nextX, this->y());
    }
    if (movingEast) {
        int nextX = ((((this->x() + 10)) > this->maxX) ? this->maxX : (this->x() + 10));
        this->setPos(nextX, this->y());
    }
    if (movingNorth) {
        int nextY = ((((this->y() - 10)) < 0) ? 0 : (this->y() - 10));
        this->setPos(this->x(), nextY);
    }
    if (movingSouth) {
        int nextY = ((this->y() + 10) > this->maxY) ? this->maxY : this->y() + 10;
        this->setPos(this->x(), nextY);

    }
}

void Player::refreshSprite() {
    if(steps % 4 == 0) {
        if(currentSprite == standing) {
            nextSprite = walkingTransition;
        }

        if(currentSprite == walkingFull) {
            nextSprite = walkingTransition;
        }

        if(currentSprite == walkingTransition) {
            nextSprite = walkingFull;
        }

        setPixmap(nextSprite.getPixmap());
        currentSprite = nextSprite;
    }
    return;
}

void Player::handleCollisions() {
    QList<QGraphicsItem *> colItems = collidingItems();
    for(QGraphicsItem* entity: colItems) {
       CollidableEntity * itemEntity = dynamic_cast<CollidableEntity*>(entity);
       itemEntity->handleCollision(this);
    }
}

void Player::setDead(bool dead) {
    this->dead = dead;
}

bool Player::isDead() {
    return this->dead;
}
