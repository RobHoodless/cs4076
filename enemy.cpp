#include "enemy.h"
#include "QDebug"

Enemy::Enemy() {
    //perhaps what I want is a sprite sheet location that has the path in string form for the image from which to generate the qimage
    spriteSheet = new QImage(":/images/enemy.png");
    standing = QPixmap::fromImage(spriteSheet->copy(0, 0, 100, 100));
    walkingTransition = QPixmap::fromImage(spriteSheet->copy(100, 0, 100, 100));
    walkingFull =  QPixmap::fromImage(spriteSheet->copy(200, 0, 100, 100));

    this->setPixmap(standing);
    currentSprite = standing;
    nextSprite = standing;
}

Enemy::Enemy(int initialX, int initialY, int movementAxis) : Enemy() {
    this->initialX = initialX;
    this->initialY = initialY;
    this->movementAxis = movementAxis;
}

void Enemy::draw() {
    setPos(this->initialX, this->initialY);
}

void Enemy::refreshSprite() {

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
void Enemy::move() {
    steps++;

    if(this->movementAxis == 0) {
        //move up
        if(this->x() <= 0) {
            movementDir = 1;
        }
        if(this->x() >= 740) {
            movementDir = -1;
        }
        this->setPos(this->x() + (5 * movementDir), this->y());

    } else {
        //move sideways
        if(this->y() <= 0) {
            movementDir = 1;
        }
        if(this->y() >= 375) {
            movementDir = -1;
        }
        this->setPos(this->x(), this->y() + (5 * movementDir));
    }
    return;
}

void Enemy::handleCollision(Player *player) {
    player->setDead(true);
    return;
}
