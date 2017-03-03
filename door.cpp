#include "door.h"

#include <QDebug>

Door::Door(int direction) {
    this->direction = direction;
}

void Door::draw() {
    if (direction == 0) { // North
        spriteSheet = new QImage(":images/door_horizontal.png");
        sprite = QPixmap::fromImage(spriteSheet->copy(0, 0, 100, 50));
        setPixmap(sprite);
        setPos(350, 0);
    } else if (direction == 1) { // East
        spriteSheet = new QImage(":/images/door.png");
        sprite = QPixmap::fromImage(spriteSheet->copy(0, 0, 50, 100));
        setPixmap(sprite);
        setPos(750, 175);
    } else if (direction == 2) { // South
        spriteSheet = new QImage(":images/door_horizontal.png");
        sprite = QPixmap::fromImage(spriteSheet->copy(0, 0, 100, 50));
        setPixmap(sprite);
        setPos(400, 450);
    } else { // West
        spriteSheet = new QImage(":/images/door.png");
        sprite = QPixmap::fromImage(spriteSheet->copy(0, 0, 50, 100));
        setPixmap(sprite);
        setPos(0, 175);
    }
}

void Door::handleCollision(Player *player) {
    this->exited = this->direction;
}

int Door::isActivated() {
    return this->exited;
}

int Door::getDirection() {
    return this->direction;
}
