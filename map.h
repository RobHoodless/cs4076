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
    Map(QGraphicsScene *scene, Player *player);
    ~Map();
    Room* changeActiveRoom(Direction direction, QGraphicsScene *scene);
    Room* getActiveRoom() const;
    void printMap(QGraphicsScene *scene);
    void removePreviousActiveCell();
    void updateActiveCell(QGraphicsScene *scene);
    int getNumItems() const;

private:
    int activeX;
    int activeY;
    vector< vector< Room* > > rooms;
    Room *activeRoom;
    void createMap(QGraphicsScene *scene, Player *player);
    void fillNeighbours(bool* neighbours, int x, int y) const;
    void removeActiveCell();
    inline void goNorth();
    inline void goEast();
    inline void goSouth();
    inline void goWest();
    int numRooms = 0;
    QGraphicsRectItem *activeCellPtr;
};

#endif // MAP_H
