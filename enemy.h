#ifndef ENEMY_H
#define ENEMY_H
#include <mobileentity.h>
#include <collidableentity.h>
#include <player.h>

class Enemy: public MobileEntity, public CollidableEntity {
public:
    Enemy();
    Enemy(int initialX, int initialY);
    void handleCollision(Player *player) override;
    void draw() override;
    void refreshSprite() override;
    void move() override;

private:
    int initialX = 0;
    int initialY = 0;
};

#endif // ENEMY_H
