#ifndef ROOM_H
#define ROOM_H

#include <QGraphicsScene>

#include <vector>

#include "entity.h"
#include "stationaryentity.h"
#include "mobileentity.h"
#include "item.h"
#include "entity.h"
#include "stationaryentity.h"
#include "mobileentity.h"
#include "player.h"
#include "door.h"

using namespace std;

class Room {
public:
    Room(QGraphicsScene *scene, Player *player);
    ~Room();
    void setup(bool n, bool e, bool s, bool w);
    void draw() const;
    void refresh() const; //redraw all mobile entities.
    void moveEntities() const; //Move all mobile entities.
    int getNextDirection() const;
    bool isExited();
    void tearDown();
    bool isPlayerDead() const;
    void createEntities();

private:
    void createDoors();
    void handleCollisions() const;
    QGraphicsScene *scene;
    Player *player;
    vector<StationaryEntity *> items;
    vector<Door *> doors;
    vector<MobileEntity *> enemies;
    bool neighbourNorth = false;
    bool neighbourEast = false;
    bool neighbourSouth = false;
    bool neighbourWest = false;
    int nextDirection;
    bool exited = false;
    int numItems = 5;
};

#endif // ROOM_H
