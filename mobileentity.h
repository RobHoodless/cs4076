#ifndef MOBILEENTITY_H
#define MOBILEENTITY_H

#include <QString>

#include "entity.h"
#include "sprite.h"

class MobileEntity : public Entity {
public:
    MobileEntity(QString filepath, int maxX, int maxY);
    virtual void move() = 0;
    virtual void refreshSprite() = 0;

protected:
    Sprite nextSprite;
    Sprite currentSprite;
    Sprite standing;
    Sprite walkingTransition;
    Sprite walkingFull;
    int maxX;
    int maxY;
};

#endif // MOBILEENTITY_H
