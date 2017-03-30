#ifndef ENEMY_H
#define ENEMY_H

#include "collidableentity.h"
#include "mobileentity.h"
#include "player.h"

class Enemy: public MobileEntity, public CollidableEntity {
public:
    Enemy(const int initialX, const int initialY, const int maxX, const int maxY, const int movementDir);
    void handleCollision(Player * const player) override;
    void draw() override;
    void refreshSprite() override;
    void move() override;

private:
    int initialX = 0;
    int initialY = 0;
    int movementAxis = 0; //0 to move in y axis, anything else is x.
    int movementDir = -1; //-1 is up or left, 1 is down or right
    int steps = 0;
};

#endif // ENEMY_H
