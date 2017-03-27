#ifndef PLAYER_H
#define PLAYER_H

#include <mobileentity.h>

#include <QSet>

class Player : public MobileEntity {

public:
    Player(int maxX, int maxY);
    void draw();
    void move();
    void refreshSprite();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void handleCollisions();
    void setDead(bool dead);
    bool isDead();

private:
    QSet<int> keysPressed;
    void processKeys();
    int maxX;
    int maxY;
    bool movingWest = false;
    bool movingEast = false;
    bool movingNorth = false;
    bool movingSouth = false;
    bool dead = false;

    int numSteps = 0;
};

#endif // PLAYER_H
