#ifndef DOOR_H
#define DOOR_H

#include "direction.h"
#include "stationaryentity.h"
#include "player.h"

class Door : public StationaryEntity {
public:
    Door(const Direction & direction);
    //Player obtainedBy();
    void handleCollision(Player *const player) override;
    void draw();
    bool isExited() const; //returns true if player collided with door
    Direction getDirection() const;

private:
    bool exited = false;
    Direction direction;
};

#endif // DOOR_H
