#ifndef ITEM_H
#define ITEM_H

#include "player.h"
#include "stationaryentity.h"

class Item : public StationaryEntity {
public:
    Item();
    Item(int initialX, int initialY);
    void draw();
    void handleCollision(Player *player);

private:
    int initialX = 0;
    int initialY = 0;
};

#endif // ITEM_H
