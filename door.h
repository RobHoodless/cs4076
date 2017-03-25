#ifndef DOOR_H
#define DOOR_H

#include <player.h>
#include <stationaryentity.h>

class Door : public StationaryEntity {
public:
    Door();
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
};




#endif // DOOR_H
