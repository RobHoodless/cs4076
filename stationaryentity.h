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
    bool isDeleted();

protected:
    string imagePath = "";
    QPixmap sprite;
    bool deleted = false;
};

#endif // STATIONARYENTITY_H
