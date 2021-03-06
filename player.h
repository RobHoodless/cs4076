#ifndef PLAYER_H
#define PLAYER_H

#include <QSet>

#include "mobileentity.h"

class Player : public MobileEntity {

public:
    Player(int maxX, int maxY);
    void draw();
    void move();
    void refreshSprite();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void handleCollisions();
    void setDead( const bool dead);
    bool isDead();
    void incrementScore();
    int getScore();
    void moveNorth();
    void moveEast();
    void moveWest();
    void moveSouth();

private:
    QSet<int> keysPressed;
    void processKeys();
    bool movingWest = false;
    bool movingEast = false;
    bool movingNorth = false;
    bool movingSouth = false;
    bool dead = false;
    int score = 0;
    int steps = 0;
};

#endif // PLAYER_H
