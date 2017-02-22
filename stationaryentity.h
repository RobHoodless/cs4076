#ifndef STATIONARYENTITY_H
#define STATIONARYENTITY_H

#include <player.h>
#include <string>

using namespace std;

class StationaryEntity : public Entity
{
public:
    StationaryEntity();
    virtual void handleCollision(Player *player) = 0;

protected:
    string imagePath = "";
    QPixmap sprite;

};

#endif // STATIONARYENTITY_H
