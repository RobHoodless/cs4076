#ifndef MOBILEENTITY_H
#define MOBILEENTITY_H

#include <sprite.h>
#include <entity.h>

class MobileEntity : public Entity {
public:
    MobileEntity();
    virtual void move() = 0;
    virtual void refreshSprite() = 0;

protected:
    Sprite nextSprite;
    Sprite currentSprite;
    Sprite standing;
    Sprite walkingTransition;
    Sprite walkingFull;

};

#endif // MOBILEENTITY_H
