#include "enemy.h"
#include "QDebug"

Enemy::Enemy() {
    spriteSheet = new QImage(":/images/enemy.png");
    standing = Sprite(QPixmap::fromImage(spriteSheet->copy(0, 0, 100, 100)));
    walkingTransition = Sprite(QPixmap::fromImage(spriteSheet->copy(100, 0, 100, 100)));
    walkingFull =  Sprite(QPixmap::fromImage(spriteSheet->copy(200, 0, 100, 100)));

    this->setPixmap(standing.getPixmap());
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
void Enemy::move() {
    steps++;

    if(this->movementAxis == 0) {
        if(this->x() <= 0) {
            movementDir = 1;
        }
        if(this->x() >= 740) {
            movementDir = -1;
        }
        this->setPos(this->x() + (5 * movementDir), this->y());

    } else {
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
