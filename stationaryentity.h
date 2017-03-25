#ifndef STATIONARYENTITY_H
#define STATIONARYENTITY_H

#include <player.h>
#include <string>
#include <collidableentity.h>

using namespace std;

class StationaryEntity : public Entity, public CollidableEntity
{
public:
    StationaryEntity();


protected:
    string imagePath = "";
    QPixmap sprite;

};

#endif // STATIONARYENTITY_H
