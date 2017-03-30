#ifndef MAP_H
#define MAP_H

#include <vector>

#include <QGraphicsScene>

#include "direction.h"
#include "player.h"
#include "room.h"

using namespace std;

class Map {
public:
    Map(QGraphicsScene * const scene, Player * const player);
    ~Map();
    Room* changeActiveRoom(const Direction & direction, QGraphicsScene *scene);
    Room* getActiveRoom() const;
    void printMap(QGraphicsScene * const scene);
    void removePreviousActiveCell();
    void updateActiveCell(QGraphicsScene * const scene);
    int getNumItems() const;

private:
    int activeX;
    int activeY;
    vector< vector< Room* > > rooms;
    Room *activeRoom;
    void createMap(QGraphicsScene * const scene, Player * const player);
    void fillNeighbours(bool * const neighbours, const int x, const int y);
    void removeActiveCell();
    inline void goNorth();
    inline void goEast();
    inline void goSouth();
    inline void goWest();
    int numRooms = 0;
    QGraphicsRectItem *activeCellPtr;
};

#endif // MAP_H
