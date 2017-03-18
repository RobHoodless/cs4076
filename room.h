#ifndef ROOM_H
#define ROOM_H

#include <QGraphicsScene>

#include <vector>

#include "entity.h"
#include "stationaryentity.h"
#include "mobileentity.h"
#include "player.h"
#include "door.h"

using namespace std;

class Room {
public:
    Room(QGraphicsScene *scene, Player *player, bool roomNorth, bool roomEast, bool roomSouth, bool roomWest);
    ~Room();
    void draw();
    void refresh(); //redraw all mobile entities.
    void moveEntities(); //Move all mobile entities.
    bool isComplete();
    int getNextDirection();
    bool getRoomNorth();
    bool getRoomEast();
    bool getRoomSouth();
    bool getRoomWest();

private:
    vector<StationaryEntity *> items;
    vector<Door *> doors;
    QGraphicsScene *scene;
    Player *player;
    vector<MobileEntity> enemies;
    void createEntities();
    void createDoors();
    void handleCollisions();
    long roomId; //used to get room details from JSON rooms info.
    void loadEntities(); //draw all entities in room
    int nextDirection;
    bool roomNorth = false;
    bool roomEast = false;
    bool roomSouth = false;
    bool roomWest = false;
};

#endif // ROOM_H
