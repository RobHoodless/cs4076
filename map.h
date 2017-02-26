#ifndef MAP_H
#define MAP_H

#include <vector>

using namespace std;

class Map {
public:
    Map();
    int getActiveX();
    int getActiveY();
    void printMap();
    void getNeighbourRooms(bool* directions);

private:
    int activeX;
    int activeY;
    vector<vector<bool>> rooms;
};

#endif // MAP_H
