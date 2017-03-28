#include "door.h"

#include "player.h"
#include "direction.h"
#include <QDebug>

Door::Door(Direction direction) {
    this->direction = direction;
}

void Door::draw() {
    if (direction == NORTH) {
        spriteSheet = new QImage(":images/door_horizontal.png");
        sprite = QPixmap::fromImage(spriteSheet->copy(0, 0, 100, 50));
        setPixmap(sprite);
        setPos(350, 0);
    } else if (direction == EAST) {
        spriteSheet = new QImage(":/images/door.png");
        sprite = QPixmap::fromImage(spriteSheet->copy(0, 0, 50, 100));
        setPixmap(sprite);
        setPos(750, 175);
    } else if (direction == SOUTH) {
        spriteSheet = new QImage(":images/door_horizontal.png");
        sprite = QPixmap::fromImage(spriteSheet->copy(0, 0, 100, 50));
        setPixmap(sprite);
        setPos(400, 400);
    } else if (direction == WEST) {
        spriteSheet = new QImage(":/images/door.png");
        sprite = QPixmap::fromImage(spriteSheet->copy(0, 0, 50, 100));
        setPixmap(sprite);
        setPos(0, 175);
    }
}

void Door::handleCollision(Player *player) {
    this->exited = true;
}

bool Door::isExited() const {
    return this->exited;
}

Direction Door::getDirection() const {
    return this->direction;
}
