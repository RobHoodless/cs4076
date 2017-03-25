#include "enemy.h"

Enemy::Enemy() {
    //perhaps what I want is a sprite sheet location that has the path in string form for the image from which to generate the qimage
    spriteSheet = new QImage(":/images/enemy.png");
    standing = QPixmap::fromImage(spriteSheet->copy(0, 0, 100, 100));
    walkingTransition = QPixmap::fromImage(spriteSheet->copy(100, 0, 100, 100));
    walkingFull =  QPixmap::fromImage(spriteSheet->copy(200, 0, 100, 100));

    this->setPixmap(standing);
    nextSprite = standing;
}

Enemy::Enemy(int initialX, int initialY) : Enemy() {
    this->initialX = initialX;
    this->initialY = initialY;
}

void Enemy::draw() {
    setPos(this->initialX, this->initialY);
}

void Enemy::refreshSprite() {
    //setPixmap(nextSprite);
    return;
}
void Enemy::move() {
    return;
}

void Enemy::handleCollision(Player *player) {
    return;
}
