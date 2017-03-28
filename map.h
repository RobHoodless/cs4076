#ifndef MAP_H
#define MAP_H

#include <QGraphicsScene>

#include <vector>

#include "room.h"
#include "player.h"
#include "direction.h"

using namespace std;

class Map {
public:
    Map(QGraphicsScene *scene, Player *player);
    void changeActiveRoom(Direction direction);
    Room* getActiveRoom();
    void printMap(QGraphicsScene *scene) const;

private:
    int activeX;
    int activeY;
    vector< vector< Room* > > rooms;
    Room *activeRoom;
    void createMap(QGraphicsScene *scene, Player *player);
    void getNeighbourRooms(bool* directions, int x, int y) const;
    inline void goNorth();
    inline void goEast();
    inline void goSouth();
    inline void goWest();
};

#endif // MAP_H
