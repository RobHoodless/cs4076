#ifndef STATIONARYENTITY_H
#define STATIONARYENTITY_H

#include <string>

#include "collidableentity.h"
#include "player.h"

using namespace std;

class StationaryEntity : public Entity, public CollidableEntity
{
public:
    StationaryEntity();
    bool isPickedUp();

protected:
    string imagePath = "";
    QPixmap sprite;
    bool pickedUp = false;
};

#endif // STATIONARYENTITY_H
