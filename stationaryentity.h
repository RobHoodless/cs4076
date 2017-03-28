#ifndef STATIONARYENTITY_H
#define STATIONARYENTITY_H

#include "player.h"
#include <string>
#include <collidableentity.h>

using namespace std;

class StationaryEntity : public Entity, public CollidableEntity
{
public:
    StationaryEntity();
    bool isDeleted();

protected:
    string imagePath = "";
    QPixmap sprite;
    bool deleted = false;

};

#endif // STATIONARYENTITY_H
