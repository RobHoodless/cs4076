#ifndef COLLIDABLEENTITY_H
#define COLLIDABLEENTITY_H

#include "player.h"

class CollidableEntity {
public:
    CollidableEntity();
    virtual void handleCollision(Player * const player) = 0;
};

#endif // COLLIDABLEENTITY_H
