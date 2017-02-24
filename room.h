#ifndef ROOM_H
#define ROOM_H

#include <QGraphicsScene>

#include <vector>

#include <entity.h>
#include <stationaryentity.h>
#include <mobileentity.h>
#include <player.h>

using namespace std;

class Room {
public:
    Room(QGraphicsScene *scene, Player *player, bool roomNorth, bool roomSouth, bool roomEast, bool roomWest);
    void draw();
    void refresh(); //redraw all mobile entities.
    void moveEntities(); //Move all mobile entities.
    bool isComplete();
    int getNextDirection();
    void tearDown();

private:
    vector<StationaryEntity *> items;
    QGraphicsScene *scene;
    Player *player;
    vector<MobileEntity> enemies;
    void createEntities();
    void handleCollisions();
    long roomId; //used to get room details from JSON rooms info.
    void loadEntities(); //draw all entities in room
    int nextDirection;
};

#endif // ROOM_H
