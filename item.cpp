#include "item.h"

#include <QImage>
#include <QPixmap>

Item::Item()
{
    spriteSheet = new QImage(":/images/diamond.png");
    sprite = QPixmap::fromImage(spriteSheet->copy(0,0, 50, 50));
    setPixmap(sprite);
}

Item::Item(int initialX, int initialY) : Item() {
    this->initialX = initialX;
    this->initialY = initialY;
}

void Item::draw()
{
    setPos(this->initialX, this->initialY);
}

void Item::handleCollision(Player *player)
{
    delete this;
}
