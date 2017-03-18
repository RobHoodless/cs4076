#ifndef DOOR_H
#define DOOR_H

#include "player.h"
#include "stationaryentity.h"
#include "map.h"

class Door : public StationaryEntity {
public:
    Door(Direction direction);
    //Player obtainedBy();
    void handleCollision(Player *player);
    void draw();
    bool isExited(); //returns true if player collided with door
    Direction getDirection();

private:
    bool exited = false;
    Direction direction;
};

#endif // DOOR_H
