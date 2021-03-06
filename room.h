#ifndef ROOM_H
#define ROOM_H

#include <vector>

#include <QGraphicsScene>

#include "door.h"
#include "item.h"
#include "mobileentity.h"
#include "player.h"
#include "stationaryentity.h"

using namespace std;

class Room {
public:
    Room(QGraphicsScene * const scene, Player * const player);
    ~Room();
    void setup(const bool n, const bool e, const bool s, const bool w);
    void draw() const;
    void refresh() const; //redraw all mobile entities.
    void moveEntities() const; //Move all mobile entities.
    int getNextDirection() const;
    bool isExited();
    void tearDown();
    bool isPlayerDead() const;
    void createEntities();
    int getNumItems() const;

private:
    void createDoors();
    void handleCollisions() const;
    QGraphicsScene *scene;
    Player *player = nullptr;
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
