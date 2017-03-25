#ifndef MAP_H
#define MAP_H

#include <QGraphicsScene>

#include <vector>

using namespace std;

enum Direction {NORTH = 0, EAST, SOUTH, WEST};

class Map {
public:
    Map(QGraphicsScene *scene);
    int getActiveX() const;
    int getActiveY() const;
    void changeActiveRoom(Direction direction);
    void getNeighbourRooms(bool* directions) const;
    void printMap(QGraphicsScene *scene) const;

private:
    int activeX;
    int activeY;
    vector<vector<bool>> rooms;
    void createMap();
    inline void goNorth();
    inline void goEast();
    inline void goSouth();
    inline void goWest();
};

#endif // MAP_H
