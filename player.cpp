#include "player.h"

#include <QKeyEvent>
#include <QDebug>

#include <item.h>
#include <collidableentity.h>
#include "item.h"

Player::Player(int maxX, int maxY) {
    //perhaps what I want is a sprite sheet location that has the path in string form for the image from which to generate the qimage
    spriteSheet = new QImage(":/images/dragon.png");
    standing = QPixmap::fromImage(spriteSheet->copy(0, 0, 100, 100));
    walkingTransition = QPixmap::fromImage(spriteSheet->copy(100, 0, 100, 100));
    walkingFull =  QPixmap::fromImage(spriteSheet->copy(200, 0, 100, 100));

    this->setPixmap(standing);
    nextSprite = standing;

    this->maxX = maxX - 100;
    this->maxY = maxY - 100;

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

    //check if release is auto generated, if it is: ignore, otherwise flip movingDirection
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
    //set graphic
    this->setPixmap(standing);

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
    if(steps % 15 == 0) {
        if(currentSprite.toImage() == standing.toImage()) {
            nextSprite = walkingTransition;
            qDebug() << "Going to transtition" << endl;
        }

        if(currentSprite.toImage() == walkingFull.toImage()) {
            nextSprite = walkingTransition;
            qDebug() << " Going to transition" << endl;
        }

        if(currentSprite.toImage() == walkingTransition.toImage()) {
            nextSprite = walkingFull;
            qDebug() << "Going to full" << endl;
        }

        setPixmap(nextSprite);
        currentSprite = nextSprite;
    }
    return;
}

void Player::handleCollisions() {
    QList<QGraphicsItem *> colItems = collidingItems();
    for(auto & entity: colItems) {
       CollidableEntity * itemEntity = dynamic_cast<CollidableEntity*>(entity);
       //StationaryEntity * itemEntity = dynamic_cast<StationaryEntity*>(entity);
       itemEntity->handleCollision(this);
    }
}

void Player::setDead(bool dead) {
    this->dead = dead;
}

bool Player::isDead() {
    return this->dead;
}
