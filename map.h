#ifndef MAP_H
#define MAP_H

#include <vector>

using namespace std;

enum Direction {NORTH = 0, EAST, SOUTH, WEST};

class Map {
public:
    Map();
    int getActiveX() const;
    int getActiveY() const;
    void changeActiveRoom(Direction direction);
    void printMap() const;
    void getNeighbourRooms(bool* directions) const;

private:
    int activeX;
    int activeY;
    vector<vector<bool>> rooms;
    inline void goNorth();
    inline void goEast();
    inline void goSouth();
    inline void goWest();
};

#endif // MAP_H
