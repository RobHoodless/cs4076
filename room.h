#ifndef ROOM_H
#define ROOM_H

#include <QGraphicsScene>

#include <vector>

#include <entity.h>
#include <stationaryentity.h>
#include <mobileentity.h>
#include <player.h>
#include <item.h>
#include "entity.h"
#include "stationaryentity.h"
#include "mobileentity.h"
#include "player.h"
#include "door.h"

using namespace std;

class Room {
public:
    Room(QGraphicsScene *scene, Player *player, bool neighbourNorth, bool neighbourEast, bool neighbourSouth, bool neighbourWest);
    ~Room();
    void draw() const;
    void refresh() const; //redraw all mobile entities.
    void moveEntities() const; //Move all mobile entities.
    bool isComplete() const;
    int getNextDirection() const;
    bool getNeighbourNorth() const;
    bool getNeighbourEast() const;
    bool getNeighbourSouth() const;
    bool getNeighbourWest() const;
    bool isExited();
    void tearDown();

private:
    long roomId; //used to get room details from JSON rooms info.
    bool neighbourNorth = false;
    bool neighbourEast = false;
    bool neighbourSouth = false;
    bool neighbourWest = false;
    vector<StationaryEntity *> items;
    vector<Door *> doors;
    QGraphicsScene *scene;
    Player *player;
    vector<MobileEntity *> enemies;
    void createEntities();
    void createDoors();
    void handleCollisions() const;
    void loadEntities(); //draw all entities in room
    int nextDirection;
    bool exited = false;
};

#endif // ROOM_H
