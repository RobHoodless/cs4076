#include "mobileentity.h"

MobileEntity::MobileEntity(QString filepath, int maxX, int maxY)  {
    spriteSheet = new QImage(filepath);
    standing = Sprite(QPixmap::fromImage(spriteSheet->copy(0, 0, 100, 100)));
    walkingTransition = Sprite(QPixmap::fromImage(spriteSheet->copy(100, 0, 100, 100)));
    walkingFull =  Sprite(QPixmap::fromImage(spriteSheet->copy(200, 0, 100, 100)));

    this->setPixmap(standing.getPixmap());
    currentSprite = standing;
    nextSprite = standing;

    this->maxX = maxX - 100;
    this->maxY = maxY - 100;
}
