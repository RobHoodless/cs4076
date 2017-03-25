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
    //void draw();
    //int isActivated(); //returns direction room was exited

private:
    const int NORTH = 0;
    const int EAST = 1;
    const int SOUTH = 2;
    const int WEST = 3;
    bool northExit, eastExit, southExit, westExit;
    bool activated;
    int *exited = nullptr;
    void draw();
    bool isExited() const; //returns true if player collided with door
    Direction getDirection() const;
    bool exited = false;
    Direction direction;
};

#endif // DOOR_H
