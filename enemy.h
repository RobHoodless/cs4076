#ifndef ENEMY_H
#define ENEMY_H
#include <mobileentity.h>
#include <collidableentity.h>
#include <player.h>

class Enemy: public MobileEntity, public CollidableEntity {
public:
    Enemy(int initialX, int initialY, int maxX, int maxY, int movementDir);
    void handleCollision(Player *player) override;
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
